//Room: yongtai-dadao4.c

inherit ROOM;

void create ()
{
	set ("short", "��̩���");
	set ("long", @LONG
���ڽֵ������ϱ��������еĴ�֣��Ͷ����Ķ������ֻ��ཻ���
�ɡ���������������ʵ�ҹ����ȴ�������������ƻ�ͨ��������һ����
�֡�����С�ֺ��������Щ���ֽ����ã���Ȼ���򡣶�����һ����
����
LONG);
	set("exits",([//sizeof() == 3
		"south" : __DIR__"yongtai-dadao5",
		"north" : __DIR__"xian-daokou",
		"east" :__DIR__"miao"
	]));

	set("outdoors", "changan");
	setup();
}
	