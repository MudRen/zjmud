//Room: yongtai-dadao5.c

inherit ROOM;

void create ()
{
	set ("short", "��̩���");
	set ("long", @LONG
���ڽֵ������ϱ��������еĴ�֣��Ͷ����Ķ������ֻ��ཻ���
�ɡ���������������ʵ�ҹ����ȴ�������������ƻ�ͨ��������һ����
�֡�����С�ֺ��������Щ���ֽ����ã���Ȼ����
LONG);
	set("exits",([//sizeof() == 2
		"south" : __DIR__"yongtai-nankou",
		"north" : __DIR__"yongtai-dadao4",
	]));

	set("outdoors", "changan");
	setup();
}
	