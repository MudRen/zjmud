//Room: yongtai-dadao1.c

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
		"south" : __DIR__"yongtai-dadao2",
		"north" : __DIR__"yongtai-beikou",
		"east" : __DIR__"huozhan",
	]));

	set("outdoors", "changan");
	setup();
}
	