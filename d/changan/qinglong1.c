//Room: qinglong1.c

inherit ROOM;

void create ()
{
	set ("short", "������");
	set ("long", @LONG
�������ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·������
�ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء�������һ���ܾ߹�ģ����
Ժ��ż�����̾�֮��������
LONG);
	set("exits", 
	([ //sizeof() == 3
		"south" : __DIR__"baoxiangsi",
		"west" : __DIR__"fufeng5",
		"east" : __DIR__"qinglong2",
	]));

	set("outdoors", "changan");
	setup();
}
