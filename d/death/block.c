inherit ROOM;

void create()
{
	set("short","С����");
	set("long","������......�Ͻ��Ҷ��������߰ɣ�����\n");
	set("valid_startroom",1);
	set("exits", ([
		"south" : __DIR__"shenxun",
	]));
	set("objects", ([
	]));
	setup();
}
/*
void init()
{
	if (!wizardp(this_player()))
	add_action("block_cmd","",1);
}

int block_cmd()
{
	return 1;
}
*/
void init()
{
	if (!wizardp(this_player()))
	{
		this_player()->set("startroom", "/d/death/block");
		add_action("discmds",({"use","eat","fly","research","yanjiu","jiqu","derive","suicide","jobto","myshop","study","inventory","sleep","kill","fight","hit","conjure","expell","perform","prcatice","fly","exercise","respirate"}));
	}
}
int discmds()
{
	tell_object(this_player(),"������ʵ���Űɣ�����\n");
	return 1;
}