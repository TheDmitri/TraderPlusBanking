class CfgMods
{
	class DmitriAssets
	{
		dir="DmitriAssets";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="DmitriAssets";
		author="Malinin";
		version="Version 1.0";
		extra=0;
		type="mod";
		class defs
		{
			class widgetStyles
			{
				files[]=
				{
					"DmitriAssets/gui/Styles.styles"
				};
			};
			class imageSets
			{
				files[]=
				{
					"DmitriAssets/gui/Data/first.imageset"
				};
			};
		};
	};
};
class CfgPatches
{
	class DmitriAssets
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"RPC_Scripts"
		};
	};
};