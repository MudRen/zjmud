//Room: qixiang5.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
������ǳ����Ǳ�һ��������Ĵ����������ྻ������ʮ����
�֣���������������Ϣ����ֵ������̼��Ƽ������СС�ĵ��̱��ڶ�
����������һ�����ε꣬�ϱ߾��ǳ����������ĺ����ھ֡�
LONG);
	set("exits", 
	([ //sizeof() == 4
		"south" : __DIR__"biaoju-damen",
		"north" : __DIR__"shoushi-dian",
		"west" : __DIR__"qixiang4",
       		"east" : __DIR__"qixiang6",
	]));

	set("outdoors", "changan");
	setup();
}
