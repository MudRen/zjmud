//Room: liande-nankou.c

inherit ROOM;

void create ()
{
	set ("short", "�����Ͽ�");
	set ("long", @LONG
����ֵĶ���ͷ��һ�����ɶ�ߵ����֮�ϣ���������յ����ĵ�
����ÿ��ĺɫ���٣�����ƻ�ͨ����������һ��С�ƹݣ�������������
��ȭ���������������ͨ�����´����
LONG);
	set("exits", 
	([ //sizeof() == 3
		"west" : __DIR__"huarui6",
		"north" : __DIR__"liande-dadao5",
		"south" : __DIR__"xiaojiuguan"
	]));

	set("outdoors", "changan");  
	setup();
}
