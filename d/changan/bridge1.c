//Room: bridge1.c

inherit ROOM;

void create ()
{
	set ("short", "��ˮ��");
	set ("long", @LONG
��ˮ����һ��ֱͨ�ʹ��Ĵ�ʯ�ţ������������ۣ�����ù�
�񹦣����ư��磬ʹ������һ�򵱹����Ī�еĸо���������һ���峺
���ס����ѵش�����С�ӣ���ˮ��ʱײ��ʯ�ϣ��������ȵ���ˮ������
���������ű�ͨ��׻��֣������ǹʻʹ���
LONG);
	set("exits", 
	([ //sizeof() == 2
		"south" : __DIR__"huanggong",
		"north" : __DIR__"baihu2",
	]));
	set("objects", 
	([ //sizeof() == 2
		__DIR__"npc/yulinjun" : 2,
		__DIR__"npc/tongling1" : 1,
	]));

	set("outdoors", "changan");
	setup();
}
