// muwu2.c
inherit ROOM;

void create()
{
	set("short", "Сľ��");
	set("long", @LONG
����һ�䲻�Ǻܴ��ľͷ���ӣ����￴�������ҩ�ң����аڷ��Ÿ���
��ͬ����ҩ���þߺ�һЩ�Ѿ�����˵�ҩ��
LONG );
	set("exits", ([
		"south" : __DIR__"xiaodao3",
	]));
	set("objects", ([
		CLASS_D("xiaoyao") + "/xuemuh" : 1,
	]));
	setup();
}
