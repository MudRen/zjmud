//Room: baihu1.c

inherit ROOM;

void create ()
{
	set ("short", "�׻���");
	set ("long", @LONG
�׻����ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·������
�ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء������Ƿ����������
������ɭɭ�Ĵ��Σ��м���������������Ĵ����ſڡ�
LONG);
	set("exits", 
	([ //sizeof() == 2
		"west" : __DIR__"fufeng1",
		"east" : __DIR__"baihu2",
	]));

	set("objects", ([
		"/clone/npc/xunbu" : 2,
	]));
	set("outdoors", "changan");
	set("no_fight", 1);
	setup();
}

