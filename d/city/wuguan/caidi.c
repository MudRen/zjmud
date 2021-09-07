// caidi.c Modify By River

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",HIG"�˵�"NOR);
	set("long", @LONG
������һ������Ĳ�԰���������Ͳˣ��ܲ������ӣ�˿��֮�ࡣ��Χ����
�ʶ����ˣ�����Ҫ�����ˡ����ڳ��ڵò������õ��չˣ��˵����Ӳݴ�������
�Ĳ˶����Ʋ��ã�����ģ��ض����ˡ�
LONG
	);
        
	set("exits", ([
		"south" : __DIR__"houyuan",
	]) );

	set("no_fight",1);
   
	set("objects", ([
		__DIR__"npc/guanjia5" : 1,
	]));
	set("action_list", ([
		"����":"chu ��",
	]));
	setup();
}

void init()
{
	add_action("do_chu", "chu");
	add_action("do_chu", "��");        
}

int do_chu(string arg)
{
	object me = this_player(), weapon;
	int costj, costq;

	if( !arg || arg != "��" )
		return notify_fail("��Ҫ��ʲô��\n");

	if(me->query_temp("job_name")!="����") 
		return notify_fail("���������������⹤�������������! \n");

	if(me->is_busy())
		return notify_fail("��������æ����!\n");

	if(me->is_fighting())
		return notify_fail("������ս����,�޷�ר�ĸɻ�!\n");

	weapon = me->query_temp("weapon");

	if( !weapon || weapon->query("id") != "chu tou")
		return notify_fail("������ʲô�����ݣ�������\n");

	costj = random( me->query("con")/3);
	costq = random( me->query("str")/3);

	if( me->query("jing") < costj || me->query("qi") < costq){
		message_vision(HIR"$N��һ�ɣ���С�ĳ����Լ��Ľ��ϡ�"NOR"\n",me);
		me->unconcious();
		return 1;
	}
	me->receive_damage("jing", costj);
	me->add("qi", -costq);
	if( me->query_temp("mark/��") > 15 + random(5) || me->query_temp("mark/����")) {
		me->set_temp("mark/����",1);
		write(CYN"�˵ع���˵�������ɵĲ������ˣ�����Ե���ʦ��³������ȥ�����ˣ���"NOR"\n");
		return 1;
	}  
	write("������ͷ�����ŵ��ϵ��Ӳݳ���������\n");
	me->start_busy(1);
	me->add_temp("mark/��",1);
	if( me->query_skill("staff", 1) < 30 && random(10) > 6 ){
		write(HIM"���ڳ����ж����ȵ��÷���Щ���!"NOR"\n");
		me->improve_skill("staff", me->query("int") / 10);
	}
	return 1;
}
