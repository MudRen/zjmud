// menlang.c
// By River@SJ
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "��ݴ���");
	set("long", @LONG
��ݽ����ź�Ҫ�����ߣ����봩��һ�����ȡ��ȶ�����Ž��������ķ羰��
ÿ��������ɫ�����Ӽ����Ҳ�������ߵľ��룬���ɫ�������ߣ��ۻ�ɫ�ĵ�
ש����������վ��һ�����꣬���������ˣ���Ц������ӭ�������������߾ͽ�
����ݵ�ǰԺ�ˡ�
LONG);
	set("exits", ([
		"north" : __DIR__"qianting",
		"south" : "/d/city/xidajie2",
	]));

	set("no_fight",1);
	set("objects", ([
		__DIR__"npc/dizi4" : 1,
	]));
	setup();
}

int get_object(object ob)
{
	if(userp(ob))
		return 1;
	return 0;
}

int valid_leave(object me, string dir)
{
	object *obj;

	if( dir != "north" && !wizardp(me)){
//		if( me->query("combat_exp") < 3000 )
//			return notify_fail("�����ǰ����һ�죺�����ն��㻹�������ѧ�㶫���ٳ�ȥ�ɡ�\n");
/*
		if ( me->query("enter_wuguan"))
			return notify_fail("�������һ�죬��ס���ȥ·��û�й������˼ҵ�ͬ�⣬����˽����ݡ�\n");

		if (!me->query_temp("marks/���") )
			return notify_fail("�������һ�������ܵú��Ҵ����к������߰���\n");

		obj = filter_array(deep_inventory(me), (: get_object($1) :));

		if( sizeof(obj) > 0 )
			return notify_fail("�������ٺ�һЦ����͵͵��˭��ȥ��\n");
		me->delete("enter_wuguan");
		*/
	}

	return ::valid_leave(me, dir);
}
