modded class MissionServer extends MissionBase
{
	void ~MissionServer() {
	}

	void MissionServer()
	{
		Print("TraderPlusBanking mod has started !");
		GetTraderPlusBankingLogger().LogDebug("TraderPlusBanking mod has started!");
	}
};
