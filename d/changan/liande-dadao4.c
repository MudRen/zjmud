//Room: liande-dadao4.c

inherit ROOM;

void create ()
{
	set ("short", "���´��");
	set ("long", @LONG
���ڽֵ������ϱ��������еĴ�֣��Ͷ����Ķ������ֻ��ཻ���
�ɡ���������������ʵ�ҹ����ȴ�������������ƻ�ͨ��������һ����
�֡�����С�ֺ��������Щ���ֽ����ã���Ȼ���򡣶�����һ����
����
LONG);
	set("exits",([//sizeof() == 2
       		"south" : __DIR__"liande-dadao5",
		"north" : __DIR__"dongan-daokou",
	]));

	set("outdoors", "changan");
	setup();
}
	