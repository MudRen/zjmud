// Room: /d/xiakedao/hanbin.c

inherit BUILD_ROOM;

void create()
{
	set("short", "�Ϻ�֮��");
	set("long", @LONG
������Ǵ�½���϶ˣ�������ȥ��һ���޼ʵı̺�������������
����ӳ�����˶�����С֮�С�տ����ˮ�����߽�ʯ������ɳ̲�����
��ϸĭ�����������Ƴ����ƾ��������������������������������֮
�⣬ֻ���ڴ��������У�׷��������߾��硣
LONG );
	set("outdoors", "nanhai");
	set("exits", ([
		"north" : __DIR__"xkroad4",
		"west"  : __DIR__"zhuwu",
	]));
	set("max_room", 3);
	setup();
	replace_program(BUILD_ROOM);
}
