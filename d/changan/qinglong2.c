//Room: qinglong2.c

inherit ROOM;

void create ()
{
	set ("short", "������");
	set ("long", @LONG
�������ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·������
�ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء��������ǹʻʹ��Ľ�ˮ��
�ˣ�������һ����·ͨ�򳤰������š�
LONG);
	set("exits", 
	([ //sizeof() == 4
		"north" : __DIR__"bridge2",
		"south" : __DIR__"nanan-dadao",
		"west" : __DIR__"qinglong1",
		"east" : __DIR__"qinglong3",
	]));

	set("outdoors", "changan");
	setup();
}
