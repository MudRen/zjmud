//Room: liande-dadao1.c

inherit ROOM;

void create ()
{
	set ("short", "���´��");
	set ("long", @LONG
���ڽֵ������ϱ��������еĴ�֣��Ͷ����Ķ������ֻ��ཻ���
�ɡ���������������ʵ�ҹ����ȴ�������������ƻ�ͨ��������һ����
�֡�����С�ֺ��������Щ���ֽ����ã���Ȼ����
LONG);
	set("exits",([//sizeof() == 2
		"south" : __DIR__"liande-dadao2",
		"north" : __DIR__"liande-beikou",
	]));

	set("outdoors", "changan");
	setup();
}
	