//      midao.c �ܵ�
inherit ROOM;

void create()
{
	set("short", "�ܵ�");
	set("long", @LONG
����һ����խ�İ�������ɭ���£����������˻ҳ���
������������Ҳ��֪��ͨ���δ���
LONG );
	set("exits", ([
		"north" : __DIR__"mishi",
		"east" : __DIR__"neidian",
	]));
	setup();
}
