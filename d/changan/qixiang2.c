//Room: qixiang2.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
������ǳ����Ǳ�һ��������Ĵ����������ྻ������ʮ����
�֣���������������Ϣ����ֵ������̼��Ƽ������СС�ĵ��̱��ڶ�
�����ֵı���������������һ�Ҳ�ݣ���ݵĶ�����һ��ˮ���ꡣ
LONG);
	set("exits", 
	([ //sizeof() == 4
		"south" : __DIR__"fruit-shop",
		"north" : __DIR__"tea-shop",
		"west" : __DIR__"qixiang1",
		"east" : __DIR__"qixiang3",
	]));

	set("outdoors", "changan");
	setup();
}
