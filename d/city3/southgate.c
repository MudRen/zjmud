// Room: southgate.c
inherit ROOM;
string look_gaoshi();
void create()
{
	set("short", "�ϳ���");
	set("long", @LONG
���ǳɶ��ϳ��ţ��������Ϸ����š����š�����������֣���ǽ
�����ż��Źٸ���ʾ(gaoshi)��һ����ֱ����ʯ�����������졣��
���ǽ��⣬������˽�����ˡ������ǳ��
LONG
	);
	set("outdoors", "chengdu");
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));

	set("exits", ([
		"south"  : __DIR__"nanheqiaos",
		"north"  : __DIR__"southroad2",
	]));
	set("objects", ([
		"/d/city/npc/wujiang" : 1,
		"/d/city/npc/bing"    : 2,
	]));
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n�ɶ��ᶽ\n�����\n";
}
