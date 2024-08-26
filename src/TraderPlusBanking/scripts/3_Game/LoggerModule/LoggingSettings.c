class TraderPlusBankingLoggingSettings 
{
    int logLevel = 0;
    int refreshRateInSeconds = 60;

    void MakeDirectoryIfNotExists()
    {
        if(!FileExist( TraderPlusBanking_ROOT_FOLDER))
            MakeDirectory( TraderPlusBanking_ROOT_FOLDER);

        if(!FileExist( TraderPlusBanking_LOG_FOLDER))
            MakeDirectory( TraderPlusBanking_LOG_FOLDER);

        if(!FileExist( TraderPlusBanking_LOGGER_CONFIG_DIR))
            MakeDirectory( TraderPlusBanking_LOGGER_CONFIG_DIR);
        
        if(!FileExist( TraderPlusBanking_LOGGER_LOG_DIR))
            MakeDirectory( TraderPlusBanking_LOGGER_LOG_DIR);
    }

    void Save()
    {
        JsonFileLoader<TraderPlusBankingLoggingSettings>.JsonSaveFile( TraderPlusBanking_LOGGER_CONFIG_FILE, this);
    }

    static ref TraderPlusBankingLoggingSettings Load()
    {
        TraderPlusBankingLoggingSettings settings = new TraderPlusBankingLoggingSettings();

        settings.MakeDirectoryIfNotExists();

        if(FileExist( TraderPlusBanking_LOGGER_CONFIG_FILE))
        {
            JsonFileLoader<TraderPlusBankingLoggingSettings>.JsonLoadFile( TraderPlusBanking_LOGGER_CONFIG_FILE, settings);
            return settings;
        }

        settings.Save();
        return settings;
    }

}