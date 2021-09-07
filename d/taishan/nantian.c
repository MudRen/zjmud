// Room: /d/taishan/.c
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
������ʮ���̣��������̩ɽ������ڴ��������︽��ɽ�£�
Ⱥɽ�����أ����������ƣ���ؿ������޿���״������������
���߿ɵ�һ���м��������߱����¹۷壬���������ǵ���ʶ�֮·��
LONG );
	set("exits", ([
		"eastup" : __DIR__"tianjie",
		"northup" : __DIR__"yuhuang",
		"west" : __DIR__"yueguan",
		"southdown" : __DIR__"shengxian",
	]));
	set("objects",([
		__DIR__"npc/jiang" : 1,
		__DIR__"npc/wei-shi3" : 2,
	]));
	set("outdoors", "taishan");
	setup();
}

int valid_leave(object me, string dir)
{
	object ob1;
	string mengzhu;
	
	if(!( ob1 = find_living("mengzhu")) )
	ob1 = load_object("/clone/npc/meng-zhu");
	mengzhu = ob1->query("winner");

	if( dir == "northup" ) { 
		if( present("jiang baisheng", environment(me)) 
		&& me->query("id") != mengzhu)
			return notify_fail("����ʤ������ס��˵����������æ�����ڲ�����ͣ�����ɽȥ�ɣ�\n");
		else if( me->query("id") == mengzhu ) {
			message_vision(HIY "\n����ʤ�ϻ̳Ͽֵ���$N�򵹿�ͷ�������������������꣬���꣬�����꣡"NOR"\n", me);
		}	
	}

	return ::valid_leave(me, dir);
}
