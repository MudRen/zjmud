//Room: qixiang6.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
������ǳ����Ǳ�һ��������Ĵ����������ྻ������ʮ����
�֣���������������Ϣ����ֵ������̼��Ƽ������СС�ĵ��̱��ڶ�
����������һ��ҩ�꣬�����͵��˺����´����������±��ڡ�
LONG);
	set("exits", 
	([ //sizeof() == 4
		"south" : __DIR__"weapon-shop",
		"north" : __DIR__"yaopu",
		"west" : __DIR__"qixiang5",
		"east" : __DIR__"liande-beikou",
	]));

	set("outdoors", "changan");
	setup();
}
