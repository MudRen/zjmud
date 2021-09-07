// caiyuan.c Modify By River
#include <ansi.h>
inherit ROOM;

int do_jiao(string arg);

void create()
{
	set("short",HIG"��԰"NOR);
	set("long", @LONG
������һ������Ĳ�԰���������Ͳˣ��ܲ������ӣ�˿��֮�ࡣ��Χ����
�ʶ����ˣ�����Ҫ�����ˡ���԰���м��ڴ�ף�����ʢ����ˮ�����ǲ˵ؿ���
���������ˣ����ò�����ĳ��ţ���ȱˮ̫���ˡ�
LONG
	);
 
	set("exits", ([
		"west" : __DIR__"houyuan",
	]) );

	set("no_fight",1);

	set("objects", ([
		__DIR__"npc/guanjia6" : 1,
	]));
	set("action_list", ([
		"��ˮ":"jiao ˮ",
	]));
	setup();
}

void init()
{
	add_action("do_jiao", "jiao");
	add_action("do_jiao", "��");        
}

int do_jiao(string arg)
{
	object me = this_player(), weapon;
	int costj, costq;

	if ( !arg || arg != "ˮ" )
		return notify_fail("��Ҫ��ʲô��\n");

	if(me->query_temp("job_name") != "��Ȳ˵�") 
		return notify_fail("���������������⹤�������������! \n");

	if (me->is_busy())
		return notify_fail("��������æ����!\n");

	if (me->is_fighting())
		return notify_fail("������ս����,�޷�ר�ĸɻ�!\n");

	weapon = me->query_temp("weapon");

	if( !weapon || weapon->query("id") != "piao")
		return notify_fail("������ʲô��Ҩˮ����������\n");

	costj = random(me->query("con")/3);
	costq = random(me->query("str")/3);

	if( me->query("jing") < costj || me->query("qi") < costq){
		message_vision(HIR"$N�����������Ҩˮ�����ʧ���Ե����"NOR"\n",me);
		me->unconcious();
		return 1;
	}
	me->receive_damage("jing", costj);
	me->add("qi", -costq);       
	if( me->query_temp("mark/��") > (15 + random(5)) || me->query_temp("mark/����")){
		me->set_temp("mark/����", 1);
		write(CYN"��԰����˵�������ɵĲ������ˣ�����Ե���ʦ��³������ȥ�����ˣ���"NOR"\n");
		return 1;
	}  
	write("����ư�Ӹ���Ҩ��ˮ���ڲ˵��ｽ��ˮ���� \n");
	me->start_busy(1);
	me->add_temp("mark/��",1);
	if( me->query_skill("force", 1) < 30 && random(10) > 6 ){
		write(HIM"���ڽ�ˮ�ж����ڹ����÷���Щ���!"NOR"\n");
		me->improve_skill("force", me->query("int") / 10);
	}
	return 1;
}
