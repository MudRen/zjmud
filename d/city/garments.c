// Room: /city/garments.c

inherit ROOM;

void create()
{
	set("short", "���µ�");
	set("long", @LONG
�������������¹󸾳���֮��������Ҳ��������Ҳң�֬�ۺ�ɡ���Ϊ
��������ʱ�У�һֱ�����������Ե�װ�硣�����Ǹ��ܿ��˵�Ů��������
��һ������ʱ���������������Ů�˼���һ�𣬻�������������
    ���ſں�������д�ż�������(zi)����������С���ֱʡ�
LONG );
	set("exits", ([
		"down" : __DIR__"zahuopu",
		"up" : __DIR__"garments2",
	]));
	set("objects", ([
		__DIR__"npc/zeng": 1,
	]));
	set("no_fight", 1);
	setup();
}

