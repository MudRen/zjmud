// xiuxis2.c ��Ϣ��


inherit ROOM;

void create()
{
	set("short", "��Ϣ��");
	set("long", @LONG
����һ��ʯ���������м���ż��Ŵ󴲣��������ӣ������Ǹ���
Ϣ�ĵط������й�����ͣ�ʹ�˸���˯�⡣
LONG );
	set("exits", ([
		"south" : __DIR__"neiting",
	]));
	set("no_fight",1);
	set("no_steal",1);
	set("sleep_room",1);
	setup();
}
