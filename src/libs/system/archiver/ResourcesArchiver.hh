#ifndef     _RESSOURCES_ARCHIVER_HH_
# define    _RESSOURCES_ARCHIVER_HH_

# include <string>
# include <vector>

# define FILE_NAME_LENGTH   100
# define SIZE_FILE_LENGTH   12
# define END_OF_ARCHIVE     "EOA"

namespace TBSystem {
    class ResourcesArchiver
    {
        public:
            /**
            * ResourcesArchiver Constructor
            *
            * @param Output archive name
            * @param Type of the archive (default : ar)
            */
            ResourcesArchiver(const std::string &, const std::string &e = "ar");

            /**
            * ResourcesArchiver Destructor
            */
            ~ResourcesArchiver(void);

        public:
            /**
            * Add a file in the archive
            *
            * @param File path
            */
            bool add(const std::string &);

            /**
            * Add all directory files in the archive
            *
            * @param Directory path
            */
            bool addDirectory(const std::string &);

            /**
            * Create the archive
            */
            void pack(void) const;

            /**
            * Unpack an archive content in a particular path
            *
            * @param Archive content
            * @param Destination path
            */
            static bool unpack(const char *, const std::string &);

        private:
            const std::string readFile(const std::string &path) const;
            static void formatName(std::string &name);

        private:
            const std::string _name;
            const std::string _extension;
            std::vector<std::string> _files;
    };
}

#endif /*!_RESSOURCES_ARCHIVER_HH_*/
