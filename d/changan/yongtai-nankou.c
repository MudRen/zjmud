//Room: yongtai-nankou.c

inherit ROOM;

void create ()
{
	set ("short", "��̩�Ͽ�");
	set ("long", @LONG
����ֺ���̩����Ľ���ڣ�һ�����ɶ�ߵ����֮�ϣ���������
յ����ĵ�����ÿ��ĺɫ���٣�����ƻ�ͨ����������һ�Ұ����̣���
��ͨ����̩�����
LONG);
	set("exits", 
	([ //sizeof() == 1
		"east" : __DIR__"huarui1",
		"north" : __DIR__"yongtai-dadao5",
		"south" : __DIR__"baozipu"
	]));

	set("outdoors", "changan");  
	setup();
}
