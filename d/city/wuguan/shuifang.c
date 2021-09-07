//shuifang.c
// Modify By River@SJ

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"ˮ��"NOR);
	set("long", @LONG
һ���ݣ��㿴�����ڷ��ż��ڴ�ף�gang����������װˮ�õģ���������
�����ǿյġ�һȺ��ݵĵ�������æµ������ˮ��ˮ��������һ��ߺ���ţ���
�����˲�Ҫ͵����
LONG
	);
        
	set("item_desc",([
		"gang" :"һ��ˮ�ף�������յ�����һ��ˮҲû�С�\n",
	]));

	set("exits", ([
		"west" : __DIR__"shilu2",               
	]));

	set("no_fight",1);
        
	set("objects", ([
		__DIR__"npc/guanjia4" : 1,
	]));
	set("action_list", ([
		"��ˮ":"tiao ˮ",
	]));
	setup();
}

void init()
{
	add_action("do_tiao", "tiao");
	add_action("do_tiao", "��");       
}

int do_tiao(string arg)
{
	object me = this_player(), weapon;
	int costj, costq;

	if ( !arg || arg != "ˮ" )
		return notify_fail("��Ҫ��ʲô��\n");

	if(me->query_temp("job_name") != "��ˮ") 
		return notify_fail("���������������⹤�������������! \n");

	if (me->is_busy())
		return notify_fail("��������æ����!\n");

	if (me->is_fighting())
		return notify_fail("������ս����,�޷�ר�ĸɻ�!\n");

	weapon = me->query_temp("weapon");
	if( !weapon || weapon->query("id") != "shui tong")         
		return notify_fail("������ʲô����ˮ��������\n");

	costj = random( me->query("con")/3);
	costq = random( me->query("str")/3);

	if( me->query("jing") < costj || me->query("qi") < costq){
		message_vision(HIR"$N��һ������С��ˮͰ�����Լ����ϡ�"NOR"\n",me);
		me->unconcious();
		return 1;
	}        
	me->receive_damage("jing", costj);
	me->add("qi", -costq);

	if( me->query_temp("mark/��") > 15 + random(5) || me->query_temp("mark/����")) {
		me->set_temp("mark/����", 1);
		write(CYN"ˮ������˵�������ɵĲ������ˣ�����Ե���ʦ��³������ȥ�����ˣ���"NOR"\n");
		return 1;
	}
	write("��������ˮͰ�е�ˮ������Ȼ����ˮ���С�\n");
	me->start_busy(1);
	me->add_temp("mark/��", 1);
	if( me->query_skill("parry", 1) < 30 && random(10) > 6 ){
		write(HIM"������ˮ�ж����мܵ��÷���Щ���!"NOR"\n");
		me->improve_skill("parry", me->query("int") / 10 );
	}
	return 1;
}
