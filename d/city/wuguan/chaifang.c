// chaifang.c
// Modify By River@SJ

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",HIG"��"NOR);
	set("long", @LONG
�ս��ݾͱ����ﶣ�����ѵ�����������������ϸһ��������������ɲ�
�ݡ��ܶ���æµ����ǽ�����������ر������һ�߶������Ѿ���̵�ľͷ��
������һ�����õĲ�ȴ�������ࡣ
LONG
	);
        
	set("exits", ([
		"east" : __DIR__"houyuan",
	]));

	set("no_fight",1);

	set("objects", ([
		__DIR__"npc/guanjia1" : 1,
	]));
	set("action_list", ([
		"����":"pi ��",
	]));
	setup();
}

void init()
{
	add_action("do_pi", "pi");
	add_action("do_pi", "��");       
}

int do_pi(string arg)
{
	object me = this_player(), weapon;
	int costj, costq;

	if ( !arg || arg != "��" )
		return notify_fail("��Ҫ��ʲô��������\n");

	if(me->query_temp("job_name")!="����") 
		return notify_fail("���������������⹤�������������! \n");

	if (me->is_busy())
		return notify_fail("��������æ����!\n");

	if (me->is_fighting())
		return notify_fail("������ս����,�޷�ר�ĸɻ�!\n");

	weapon = me->query_temp("weapon");

	if( !weapon || weapon->query("id") != "chai dao")
		return notify_fail("������ʲô������������\n");

	costj = random( me->query("con")/3);
	costq = random( me->query("str")/3);

	if ( me->query("jing") < costj || me->query("qi") < costq){
		message_vision(HIR"$N��һ�ᣬ��С�������Լ�������"NOR"\n",me);
		me->unconcious();
		return 1;
	}

	me->receive_damage("jing", costj);
	me->add("qi", -costq);

	if( me->query_temp("mark/��") > 15 + random(5) || me->query_temp("mark/����")) {
		me->set_temp("mark/����",1);
		write(CYN"�񷿹���˵�������ɵĲ������ˣ�����Ե���ʦ��³������ȥ�����ˣ���"NOR"\n");
		return 1;
	}
	write("�����һ��ľͷ��һ��������ȥ�����ѡ���һ����ľͷ����Ϊ��Ƭ��\n");
	me->start_busy(1);
	me->add_temp("mark/��",1);
	if( me->query_skill("blade", 1) < 30 && random(10) > 6 ){
		write(HIM"���������ж��ڵ����÷���Щ���!"NOR"\n");
		me->improve_skill("blade",  me->query("int") / 10 );
	}
	return 1;
}
