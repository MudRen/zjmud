inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
������ǿ��������Ĵ������൱�Ŀ����������ܵ�ǽ���������˸�����
�˵��漣����������һ�����Ż���ӣ�����Ц�ݵ����ӣ��Ǿ��ǵ�����ϵĳ�
���������ˡ����Ե���λ�ֱ�����������ǰ�������������Ͽ���Ʒλ�ƺ����͡�
������������һ�����ȣ�����ͨ���������������ڡ�
LONG );
	set("exits", ([
		"north" : __DIR__"kangfu_zoulang2",
		"south" : __DIR__"kangfu_zoulang1",
	]));
	set("objects", ([
		__DIR__"npc/kangqinwang" : 1,
		__DIR__"npc/zhangkang" : 1,
		__DIR__"npc/zhaoqi" : 1,
	]));
	set("outdoors", "beijing");
       setup();
}

