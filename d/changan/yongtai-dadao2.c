//Room: yongtai-dadao2.c

inherit ROOM;

void create ()
{
	set ("short", "��̩���");
	set ("long", @LONG
���ڽֵ������ϱ��������еĴ�֣��Ͷ����Ķ������ֻ��ཻ���
�ɡ���������������ʵ�ҹ����ȴ�������������ƻ�ͨ��������һ����
�֡�����С�ֺ��������Щ���ֽ����ã���Ȼ���򡣶��洫��һ��
��������ĺ�������֪����ʲô�ط���
LONG);
	set("exits",([//sizeof() == 2
		"south" : __DIR__"yongtai-dadao3",
		"north" : __DIR__"yongtai-dadao1",
		"east"  : "/d/pk/entry",
	]));

	set("outdoors", "changan");
	setup();
}
