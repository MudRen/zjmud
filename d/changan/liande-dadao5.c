//Room: liande-dadao5.c

inherit ROOM;

void create ()
{
	set ("short", "���´��");
	set ("long", @LONG
���ڽֵ������ϱ��������еĴ�֣��Ͷ����Ķ������ֻ��ཻ���
�ɡ���������������ʵ�ҹ����ȴ�������������ƻ�ͨ��������һ����
�֡�����С�ֺ��������Щ���ֽ����ã���Ȼ����
LONG);
	set("exits",([//sizeof() == 3
		"south" : __DIR__"liande-nankou",
		"north" : __DIR__"liande-dadao4",
		"east" : __DIR__"xiaojia-qianyuan",
	]));

	set("outdoors", "changan");
	setup();
}
	