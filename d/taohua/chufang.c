// Room: chufang.c
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����һ����ĳ�����������Ŵ�Բ������Χ����ż������Ρ�����
�����ż���ˮ�ɻ���������һ�±��ӣ������������㣡Ҳ��֪�����ǻ�
�㻹�Ƿ��㡣ƽʱ�һ����ĵ��Ӻ����˶��������ò͡�
LONG );
	set("exits",([
	    "east" :__DIR__"qianyuan",
	]));

	set("objects", ([
	    __DIR__"npc/yan" : 1,
	    __DIR__"npc/yapu" : 1,
	]) );

	set("resource/water", 1);

	setup();
}
int valid_leave(object me, string dir)
{
	if (dir == "east" && present("gao", me) )
	    return notify_fail("��Ӣ΢Ц��˵��������ʳ�����ȥ��\n");
	if (dir == "east" && present("zuixian cha", me) ) 
	    return notify_fail("��Ӣ΢Ц��˵��������ʳ�����ȥ��\n");
	return ::valid_leave(me, dir);
}
