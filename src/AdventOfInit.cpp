#include <vector>
#include <string>
#include <chrono>
#include <format>
#include <cpr/cpr.h>
#include <iostream>
#include <fstream>
#include <optional>
#include <filesystem>

struct ConfigBuilder
{
    struct Config
    {
        const short year;
        const unsigned char day;
        const std::filesystem::path path;
        const std::filesystem::path tmplt;
        const std::string session;

        Config(short y, unsigned char d, std::string fp, std::string session_cookie, std::string tmp)
            : year(y), day(d), path(std::move(fp)), session(std::move(session_cookie)), tmplt(std::move(tmp))
        {
            std::cout << std::format("Created Configuration:\nyear={}\nday={}\npath=\"{}\"\ntemplate=\"{}\"\nsession=\"{}\"\n", year, day, path.string(), tmplt.string(), session);
        }
    };

    auto build() -> Config
    {
        using namespace std::chrono;
        const auto date = year_month_day{time_point_cast<days>(system_clock::now())};

        auto year = _year ? *_year : static_cast<int>(date.year());                    // Set Year to current year
        year = (static_cast<unsigned>(date.month()) < 12 && !_year) ? year - 1 : year; // If current year check if already December (if was set to current year)
        year = year < 2015 && _year ? 2015 : year;                                     // No AoC before 2015 (only if specifiy year was specified)

        auto day = _day ? *_day : static_cast<unsigned>(date.day()); // Set day to current day by default
        day = day > 25 ? 1 : day;                                    // No days larger than 25

        const auto tmplt = _template ? *_template : ""; // No template directory was specified
        return Config(year, day, _path ? std::move(*_path) : std::format("./{}/Day{:02}", year, day), std::move(getCookie()), tmplt);
    }

    void setPath(std::string fp) { _path = std::move(fp); }
    void setYear(const int y) { _year = y; }
    void setDay(const int d) { _day = d; }
    void setSession(const std::string &session) { _session = session; }
    void setTemplate(const std::string &path) { _template = path; }

private:
    std::optional<short> _year;
    std::optional<unsigned char> _day;
    std::optional<std::string> _path;
    std::optional<std::string> _template;
    std::optional<std::string> _session;
    const std::string SESSION_FP{"./session.txt"};

    auto tryReadCookieFromFile(const std::string &file_path) -> std::optional<std::string>
    {
        std::ifstream input_file(file_path);
        if (input_file.good())
        {
            std::cout << std::format("Reading cookie string from: \"{}\"\n", file_path);
            std::string line;
            std::getline(input_file, line);
            return line;
        }
        else
        {
            std::cout << std::format("Couldn't read file: \"{}\"\n", file_path);
            return std::nullopt;
        }
    }

    auto getCookie() -> std::string
    {
        std::ifstream inputFile;
        if (!_session)
        {
            std::cout << std::format("Didn't provide cookie using \"{}\" instead.\n", SESSION_FP);
            const auto cookie = tryReadCookieFromFile(SESSION_FP);
            return (cookie) ? *cookie : "";
        }
        else
        {
            const auto cookie = tryReadCookieFromFile(*_session);
            return cookie ? *cookie : *_session;
        }
    }
};

void printUsage(bool exit_value = EXIT_FAILURE)
{
    std::cout << "AdventOfInit Usage:\n\
    --path <string>\t\t==> folder in which files should be generated (default: ./<year>/Day<day>/)\n\
    --template <string>\t\t==> template file which you would like to copy into the directory\n\
    --day <integer>\t\t==> Advent of Code day to checkout (default: current day)\n\
    --year <integer>\t\t==> Event Year (default: most recent event year)\n\
    --cookie <string>\t\t==> Session Cookie to log you into AoC. Could be filepath or hex-string (default: ./session.txt)\n";
    exit(exit_value);
}

int parseInt(const std::string &str)
{
    try
    {
        return std::stoi(str);
    }
    catch (...)
    {
        std::cerr << "Error: Expected integer parameter.\n";
        printUsage();
        exit(EXIT_FAILURE);
    }
}

auto parseArgs(const std::vector<std::string> &args) -> ConfigBuilder::Config
{
    ConfigBuilder config_builder;
    for (size_t i = 0; i < args.size(); i++)
    {
        if (args[i] == "--year")
            config_builder.setYear(parseInt(args[++i]));
        else if (args[i] == "--day")
            config_builder.setDay(parseInt(args[++i]));
        else if (args[i] == "--path")
            config_builder.setPath(args[++i]);
        else if (args[i] == "--cookie")
            config_builder.setSession(args[++i]);
        else if (args[i] == "--template")
            config_builder.setTemplate(args[++i]);
        else
            printUsage(args[i] == "--help" ? EXIT_SUCCESS : EXIT_FAILURE);
    }
    return config_builder.build();
}

auto getPuzzleInput(const ConfigBuilder::Config &config) -> std::string
{
    cpr::Session session;
    const std::string url = std::format("https://adventofcode.com/{}/day/{}/input", config.year, config.day);

    session.SetCookies({{"session", config.session}});
    session.SetUrl(cpr::Url{url});

    std::cout << std::format("Retrieving puzzle input from: \"{}\"\n", url);
    cpr::Response response = session.Get();

    if (response.status_code != 200)
    {
        std::cerr << std::format("Failed to retrieve website. Status code: {}\n\
Make sure to set your session cookie correctly, so you you can be logged into your account and retrieve your puzzle input.\
Log into AoC in your browser -> Inspect element -> Application -> Cookies -> Copy the session cookie into ./session.txt.\n",
                                 response.status_code);
        exit(EXIT_FAILURE);
    }

    return response.text;
}

void createDirectories(const std::filesystem::path &path)
{
    if (std::filesystem::exists(path))
        return;

    std::cout << std::format("Creating directories: \"{}\"\n", path.string());
    try
    {
        std::filesystem::create_directories(path);
    }
    catch (const std::exception &exception)
    {
        std::cerr << std::format("Failed to create directories: \"{}\"\n", exception.what());
        exit(EXIT_FAILURE);
    }
}

void writePuzzleInputFile(const ConfigBuilder::Config &config, const std::string &input)
{
    const std::string file_path = config.path.string() + "/input.txt";
    std::ofstream output_file(file_path);
    std::cout << std::format("Writing retrieved input to: \"{}\"\n", file_path);
    output_file << input << '\n';
}

template <typename T>
void replaceTemplateWith(std::string &input_str, const std::string &template_str, const T &substitute)
{
    if (const auto pos = input_str.find(template_str); pos != std::string::npos)
        input_str = input_str.substr(0, pos) + std::to_string(substitute) + input_str.substr(pos + template_str.size());
}

bool overWriteCheckAllowed(bool &overwrite_all, const std::string &filename)
{
    std::cout << std::format("\"{}\" already exists, would you like to overwrite it? [Y]es - Yes for [A]ll - [N]o\n", filename);
    const char user_input = std::tolower(std::cin.get());
    if (user_input == 'a' || user_input == 'y')
    {
        overwrite_all = (user_input == 'a'); // set to true if a (this function never gets called if overwrite_all is already true)
        return false;
    }
    return true;
}

bool filesAreEqualSize(const std::string &file1, const std::string &file2)
{
    return std::filesystem::file_size(file1) == std::filesystem::file_size(file2);
}

void substituteTemplates(std::string &file_path, const ConfigBuilder::Config &config)
{
    const std::string DAY_TMPLT{"@DAY@"};
    const std::string YEAR_TMPLT{"@YEAR@"};
    replaceTemplateWith(file_path, DAY_TMPLT, config.day);
    replaceTemplateWith(file_path, YEAR_TMPLT, config.year);
}

void copyAndRenameRecursive(const ConfigBuilder::Config &config)
{
    bool overwrite_all = false;
    const std::size_t template_path_len = config.tmplt.string().size();
    for (const auto &entry : std::filesystem::recursive_directory_iterator(config.tmplt))
    {
        std::string relative_file_path = entry.path().string().substr(template_path_len);
        if (entry.is_regular_file())
        {
            // Copy and rename regular files
            substituteTemplates(relative_file_path, config);
            const std::string dest_file =config.path.string() + "/" + relative_file_path;

            // checks if file already exists, is changed and for user permissions to overwrite the file
            if (!overwrite_all && std::filesystem::exists(dest_file) &&
                (filesAreEqualSize(dest_file, entry.path().string()) || overWriteCheckAllowed(overwrite_all, dest_file)))
                continue; // skips file copy

            std::cout << std::format("Copying file: \"{}\" ==> \"{}\"\n", entry.path().string(), dest_file);
            std::filesystem::copy_file(entry.path(), dest_file, std::filesystem::copy_options::overwrite_existing);
        }
        else if (entry.is_directory())
        {
            // Recreate folder structure in the destination directory
            //const std::string directory_path = std::filesystem::path(config.path).concat(entry_path.substr(template_path_len)).string();
            const std::string directory_path = config.path.string() + "/" + relative_file_path;
            if (!directory_path.empty())
                createDirectories(directory_path);
        }
    }
}

void copyTemplate(const ConfigBuilder::Config &config)
{
    if (!config.tmplt.empty() && std::filesystem::exists(config.tmplt))
        copyAndRenameRecursive(config);
    else
        std::cout << std::format("Template \"{}\" doesn't exist, skipping.\n", config.tmplt.string());
}

int main(int argc, char const *argv[])
{
    // Parse command line arguments
    const auto config = parseArgs({argv + 1, argv + argc});

    // Fetch puzzle input data from AoC website
    const auto input = getPuzzleInput(config);

    // Setup destination directoy structure
    createDirectories(config.path);

    // Copy puzzle input into destination directory
    writePuzzleInputFile(config, input);

    // Copy and rename template files from template directory into destination directory
    copyTemplate(config);

    std::cout << std::format("Successfully initialized AoC Day {} Year {}. Files have been written to \"{}\"\n", config.day, config.year, config.path.string());
    return EXIT_SUCCESS;
}
