// mafang.c Modify By River
inherit ROOM;
#include <ansi.h>

void create()
{
	set("short",HIG"���"NOR);
	set("long", @LONG
������ݵ���ǣ���������ģ����˼�ʮƥ������ǰ���ǣ�������
���տ���������ι�����㣬��ϴˢ�ø�Ǭ����������жѷ������Ѳ��ϣ�����
��һ����ۣ�������Щ��ˮ��
LONG
	);
        
	set("exits", ([
		"north" : __DIR__"shilu2",
	]));

	set("no_fight",1);

	set("objects", ([
		__DIR__"npc/guanjia3" : 1,
	]));
	set("action_list", ([
		"��ɨ��":"clean ��",
	]));
	setup();
}

void init()
{
	add_action("do_sao", "clean");
	add_action("do_sao", "sao");        
}

int do_sao(string arg)
{
	object me = this_player(), weapon;
	int costj, costq;

	if ( !arg || arg != "��" )
		return notify_fail("��Ҫ��ɨʲô��\n");

	if(me->query_temp("job_name")!="��ɨ��") 
		return notify_fail("���������������⹤�������������! \n");

	if (me->is_busy())
		return notify_fail("��������æ����!\n");

	if (me->is_fighting())
		return notify_fail("������ս����,�޷�ר�ĸɻ�!\n");

	weapon = me->query_temp("weapon");
	if( !weapon || weapon->query("id") != "sao zhou")
		return notify_fail("������ʲô����ɨ������ɨ��\n");

	costj = random( me->query("con")/3);
	costq = random( me->query("str")/3);

	if( me->query("jing") < costj || me->query("qi") < costq){
		message_vision(HIR"$N��һ������С�Ļ���������"NOR"\n",me);
		me->unconcious();
		return 1;
	}
	me->receive_damage("jing", costj);
	me->add("qi", -costq);
	if( me->query_temp("mark/ɨ") > 15 + random(5) || me->query_temp("mark/����")) {
		me->set_temp("mark/����",1);
		write(CYN"������˵�������ɵĲ������ˣ�����Ե���ʦ��³������ȥ�����ˣ���"NOR"\n");
		return 1;
	}
	write ("�����˸��ط���ʼɨ���������湻���ģ��㲻�ɱս��˺�����\n");
	me->start_busy(1);
	me->add_temp("mark/ɨ",1);
	if( me->query_skill("club", 1) < 30 && random(10) > 6 ){
		write(HIM"����ɨ���ж��ڹ����÷���Щ���!"NOR"\n");
		me->improve_skill("club", me->query("int") / 10 );
	}
	return 1;
}
