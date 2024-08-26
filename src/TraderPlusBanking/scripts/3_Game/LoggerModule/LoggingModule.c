
static ref TraderPlusBankingLoggingModule GetTraderPlusBankingLogger()
{
    return TraderPlusBankingLoggingModule.Cast(CF_ModuleCoreManager.Get(TraderPlusBankingLoggingModule));
}

[CF_RegisterModule(TraderPlusBankingLoggingModule)]
class TraderPlusBankingLoggingModule : CF_ModuleGame
{
    private int networkSync_LogLevel;

    ref TraderPlusBankingLoggingSettings settings;

    FileHandle fileHandle;

    float dtime = 0;


    override void OnInit()
    {
        super.OnInit();
        
        EnableUpdate();
        EnableMissionStart();
    }

    override void OnMissionStart(Class sender, CF_EventArgs args)
    {
        super.OnMissionStart(sender, args);

        fileHandle = CreateNewLogFile();

        if(GetGame().IsServer())
        {
            settings = TraderPlusBankingLoggingSettings.Load();

            networkSync_LogLevel = settings.logLevel;
            SynchLogLevel();       
        }
        else
        {
            AddLegacyRPC("GetLogLevelResponse", SingleplayerExecutionType.Client);
        }
    }

    void GetLogLevelResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		 if (type != CallType.Client)
			 return;

		 Param1<int> data;
		 if (!ctx.Read(data))
            return;

		 networkSync_LogLevel = data.param1;
	}

    void SynchLogLevel()
    {
        GetRPCManager().SendRPC(ClassName(), "GetLogLevelResponse",  new Param1<int>(networkSync_LogLevel), true, NULL);
    }

    override void OnUpdate(Class sender, CF_EventArgs args)
    {
        auto update = CF_EventUpdateArgs.Cast(args);

        if(!GetGame().IsServer())
            return;

        if(!settings)
            return;

        dtime += update.DeltaTime;
        if(dtime >= settings.refreshRateInSeconds)
        {
            dtime = 0;

            settings = TraderPlusBankingLoggingSettings.Load();

            networkSync_LogLevel = settings.logLevel;
            SynchLogLevel();
        }
    }


    void MakeDirectoryIfNotExists()
    {
        if(!FileExist(TraderPlusBanking_ROOT_FOLDER))
            MakeDirectory(TraderPlusBanking_ROOT_FOLDER);

        if(!FileExist(TraderPlusBanking_LOG_FOLDER))
            MakeDirectory(TraderPlusBanking_LOG_FOLDER);

        if(!FileExist(TraderPlusBanking_LOGGER_CONFIG_DIR))
            MakeDirectory(TraderPlusBanking_LOGGER_CONFIG_DIR);
        
        if(!FileExist(TraderPlusBanking_LOGGER_LOG_DIR))
            MakeDirectory(TraderPlusBanking_LOGGER_LOG_DIR);
    }
    
    string GenerateShortDateString()
    {
        int year, month, day;
        GetYearMonthDay(year, month, day);
        return "" + year + "_" + month + "_" + day;
    }

    string GenerateShortTimeString()
    {
        int hour, minute, second;
        GetHourMinuteSecond(hour, minute, second);
        return "" + hour + "_" + minute + "_" + second;
    }

    string GenerateFullTimestamp()
    {
        string dateStr = GenerateShortDateString();
        string timeStr = GenerateShortTimeString();

        return dateStr + "-" + timeStr;
    }

    FileHandle CreateNewLogFile()
    {
        MakeDirectoryIfNotExists();

        string filePath = string.Format(TraderPlusBanking_LOGGER_LOG_FILE, GenerateFullTimestamp());

        fileHandle = OpenFile(filePath, FileMode.WRITE);

        if(fileHandle != 0)
        {
            FPrintln(fileHandle, "Creation Time: " + GenerateFullTimestamp());
            return fileHandle;
        }

        return null;
    }

    void Log(string content, TraderPlusBankingLogLevel logLevel)
    {
        if(logLevel < networkSync_LogLevel)
            return;
        
        string timestamp = GenerateShortTimeString();
        FPrintln(fileHandle, timestamp + " | " + GetLogLevelString(logLevel) + " | " + content);
    }

    void LogInfo(string content)
    {
        Log(content, TraderPlusBankingLogLevel.Info);
    }

    void LogWarning(string content)
    {
        Log(content, TraderPlusBankingLogLevel.Warn);
    }

    void LogError(string content)
    {
        Log(content, TraderPlusBankingLogLevel.Error);
    }

    void LogDebug(string content)
    {
        Log(content, TraderPlusBankingLogLevel.Debug);
    }

    string GetLogLevelString(TraderPlusBankingLogLevel logLevel)
    {
        switch(logLevel)
        {
             case TraderPlusBankingLogLevel.Debug:
                return "DEBUG";
            case TraderPlusBankingLogLevel.Info:
                return "INFO";
            case TraderPlusBankingLogLevel.Warn:
                return "WARNING";
            case TraderPlusBankingLogLevel.Error:
                return "ERROR";
            default:
                return "";
        }

        return "";
    }

}