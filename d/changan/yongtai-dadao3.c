//Room: yongtai-dadao3.c

inherit ROOM;

void create ()
{
	set ("short", "��̩���");
	set ("long", @LONG
���ڽֵ������ϱ��������еĴ�֣��Ͷ����Ķ������ֻ��ཻ���
�ɡ���������������ʵ�ҹ����ȴ�������������ƻ�ͨ��������һ����
�֡�����С�ֺ��������Щ���ֽ����ã���Ȼ����
LONG);
	set("exits",([//sizeof() == 4
		"south" : __DIR__"xian-daokou",
		"north" : __DIR__"yongtai-dadao2",
		"east" : __DIR__"huiwenge",
	]));

	set("outdoors", "changan");
	setup();
}
	