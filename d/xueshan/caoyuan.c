//      caoyuan.c ��ԭ
inherit ROOM;

void create()
{
	set("short", "��ԭ");
	set("long", @LONG
������ѩɽ���µ�һƬ��ԭ�������������Ⱥɽ��ɽ
���ϻ������겻����ѩ��������һ����·��
LONG );

	set("exits", ([
		"west"      : __DIR__"tulu1",
		"northeast" : "/d/xingxiu/silk4" ,
	]));

	set("objects", ([
		__DIR__"npc/yetu" : 4 ,
	]));

	set("outdoors","xiyu");

	setup();
}
