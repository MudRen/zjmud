//Room: liande-beikou.c

inherit ROOM;

void create ()
{
	set ("short", "���±���");
	set ("long", @LONG
����ֵĶ���ͷ��һ�����ɶ�ߵ����֮�ϣ���������յ����ĵ�
����ÿ��ĺɫ���٣�����ƻ�ͨ����������һ�������������������
Ϸ���������Ϸ�ͨ�����´����
LONG);
	set("exits", 
	([ //sizeof() == 3
		"west" : __DIR__"qixiang6",
		"north" : __DIR__"xiyuan",
		"south" : __DIR__"liande-dadao1"
	]));

	set("outdoors", "changan");  
	setup();
}
