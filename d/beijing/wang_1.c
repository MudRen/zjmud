inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
������Ǿ�����Ϊ��������������֡�������������æ�Ľֵ��ϣ��ֵ���
��ˮ�������������������ַǷ����ϱ��Ǿ��ǵĽ�ͨҪ���������֡�������һ
�������ûʵĽ��������ǵ������ϵĵ�һ�購����Τ��ү�ĸ�ۡ�����߲�Զ��
���ǵ��̳����ǳ�͢�����շ��ĳ�����
LONG );
       set("exits", ([
		"north" : __DIR__"wang_3",
		"south" : __DIR__"caroad_e1",
		"east" : __DIR__"wang_2",
		"west" : __DIR__"weifu_men",
	]));
	set("objects", ([
		__DIR__"npc/youren" : 1,
	]));

	setup();
       set("outdoors", "beijing");
}

