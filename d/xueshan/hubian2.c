//      hubian2.c ����С·
inherit ROOM;

void create()
{
	set("short", "����С·");
	set("long", @LONG
����ʥ���ߵ�С·������Խ������������ż���а�
ɫˮ���Ӻ���ˮ������ȦȦ������
LONG );
	set("outdoors", "xueshan");
	set("exits", ([
		"northeast" : __DIR__"hubian3",
		"west" : __DIR__"hubian1",
	]));
	setup();
}
