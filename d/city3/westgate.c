// Room: westgate.c
inherit ROOM;
string look_gaoshi();
void create()
{
	set("short", "����");
	set("long", @LONG
���������������⣬ֻ���ߴ�ĳ�ǽ��ʵ���أ�������ϸ���̲�
�Ź������ˣ�һ�ж��Եþ�����������ǽ�����ż��Ÿ�ʾ(gaoshi)��
����ԶԶ���Կ����������Ϫ��ˮ�������ǳ��
LONG );
	set("outdoors", "chengdu");
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));
	set("exits", ([
		"west"  : __DIR__"nanheqiaow",
		"east"  : __DIR__"westroad2",
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
