// /guanwai/tulu.c

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
����һ���û����̾͵ĵ�·������������������ƺ��ڰ���ʯ�ϡ�
��̧ͷ������һ��������ʯ�ϵĳ������������ж�ȥ����һ�����Ŀճ�
ȴԴԴ���ϵĿ��򶫱ߡ�ֱŪ����·�ϳ������
LONG );
	set("exits", ([
		"east" : __DIR__"shichang",
		"northwest" : __DIR__ "nancheng",
	]));

	set("outdoors", "guanwai");
	setup();
}

