//Room: bridge2.c

inherit ROOM;

void create ()
{
	set ("short", "��ˮ��");
	set ("long", @LONG
��ˮ����һ��ֱͨ�ʹ��Ĵ�ʯ�ţ������������ۣ�����ù�
�񹦣����ư��磬ʹ������һ�򵱹����Ī�еĸо���������һ���峺
���ס����ѵش�����С�ӣ���ˮ��ʱײ��ʯ�ϣ��������ȵ���ˮ������
���������ű�ͨ��ʻʹ��������������֡�
LONG);
	set("exits", 
	([ //sizeof() == 2
		"south" : __DIR__"qinglong2",
		"north" : __DIR__"huanggong",
	]));
	set("objects", 
	([ //sizeof() == 1
		__DIR__"npc/yulinjun" : 2,
		__DIR__"npc/tongling2" : 1,
	]));

	set("outdoors", "changan");
	setup();
}
