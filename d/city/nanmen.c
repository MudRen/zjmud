// Room: /city/nanmen.c
inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
�����ϳ��ţ���ǽ�������˹���ƣ������˻������̸��и�ҵ�Ĺ�棬
�ٸ��ĸ�ʾ��˲�̫��Ŀ���ٱ��Ǳ������Ļ���Ц������������
�����Ǻ�������ִ�ڡ�һ����ֱ����ʯ�������ϱ��������졣
LONG );
	set("outdoors", "city");
	set("item_desc", ([
		"����ʾ��" : (: look_gaoshi :),
	]));

	set("exits", ([
		"south" : "/d/wudang/wdroad1",
		"north" : __DIR__"nandajie2",
		"west"  : __DIR__"jiaowai8",
		"east"  : __DIR__"jiaowai7",
	]));
	set("objects", ([
		__DIR__"npc/wujiang" : 1,
		__DIR__"npc/bing" : 2,
		__DIR__"npc/shisong" : 1,
	]));
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n����֪��\n��ҩ��\n";
}

