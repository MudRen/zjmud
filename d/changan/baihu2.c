//Room: baihu2.c

inherit ROOM;

void create ()
{
	set ("short", "�׻���");
	set ("long", @LONG
�׻����ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·������
�ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء����Ͼ��ǹʻʹ��Ľ�ˮ��
�ˣ�������һ����·ͨ�򳤰��Ǳ��š�
LONG);
	set("exits", ([ //sizeof() == 4
		"south" : __DIR__"bridge1",
		"north" : __DIR__"beian-dadao",
		"west" : __DIR__"baihu1",
		"east" : __DIR__"baihu3",
	]));

	set("objects", ([
		"/clone/npc/walker" : 1,
	]));

	set("outdoors", "changan");
	setup();
}
