// exercise.c
#pragma save_binary
#include <skill.h>
#include <ansi.h>
inherit F_CLEAN_UP;
int exercising(object me);
int halt_exercise(object me);

int main(object me, string arg)
{
      
	int exercise_cost;
	mapping map_temp;
	object where;
	seteuid(getuid());
	where = environment(me);
	map_temp = me->query_skill_map();  
	if ((int)me->query_skill("force",1)<10)
		return notify_fail("�㻹����ѧЩ�������ŵļ��ɣ�\n");
	if (sizeof(map_temp)!=0)
	{
		if(undefinedp(map_temp["force"]))
		{
			return notify_fail("����Ҫ��װ��(enable)�ڹ��ķ��ɣ�����\n");
		}
		else if((int)me->query_skill(map_temp["force"])<10)
		{
			return notify_fail("��װ�����ڹ��ķ�����̫���ˣ�����\n");
		}
	}
	else
	{
	     return notify_fail("����Ҫ��װ��(enable)�ڹ��ķ��ɣ�����\n");
	}
	if (where->query("pigging"))
		return notify_fail("�㻹��ר�Ĺ���ɣ�\n");
	if (me->is_busy() || me->query_temp("pending/exercising"))
		return notify_fail("��������æ���ء�\n");
	if( environment(me)->query("no_dazuo") )
		return notify_fail("�������Ƿ�֮�أ����ɾ������������ˣ����߰ɣ�\n");
	if( me->is_fighting() )
		return notify_fail("ս���в������ڹ������߻���ħ��\n");
	if( !arg || !sscanf(arg, "%d", exercise_cost))
	{
		me->set_temp("pending/auto_dazuo",1);
		exercise_cost = me->query("max_neili")/3;
		if (exercise_cost > me->query("qi") / 2) exercise_cost = me->query("qi") / 2;
		if (exercise_cost < 10 ) exercise_cost = 10;
	}
	if (exercise_cost < 10)
		return notify_fail("����ڹ���û�дﵽ�Ǹ����磡\n");
	if( (int)me->query("qi") < exercise_cost )
		return notify_fail("�����ڵ���̫���ˣ��޷�������Ϣ����ȫ������\n");
	if( (int)me->query("jing") * 100 / (int)me->query("max_jing") < 60 )
		return notify_fail("�����ھ��������޷�������Ϣ��������\n");
	write(HIR"����������ʼ����"+HIY"��"+to_chinese(map_temp["force"])+"��"+NOR+"\n"+NOR+"һ��"+HIW"��Ϣ("+exercise_cost+")"+NOR+"��ʼ����������......"+NOR+"\n");	
	me->set_temp("pending/exercise", 1);
	me->set_temp("exercise_cost", exercise_cost);
	message("vision",me->name()+"��ϥ���£���ʼ����������\n",environment(me),({me}));
	tell_object(me,ZJEXIT"northwest:"RED"վ����"NOR":halt\n");
	me->set_temp("dazuo/step", 1);
	me->start_busy(bind((: call_other, __FILE__, "exercising" :), me),
		       bind((: call_other, __FILE__, "halt_exercise" :), me));
	return 1;
}

void auto_dazuo(object me, int exercise_cost)
{
	if(!me||!me->query_temp("pending/auto_dazuo"))
		return;
	if(me->is_busy())
		call_out("auto_dazuo",1,me,exercise_cost);
	else if( (int)me->query("qi") < exercise_cost )
	{
		if (SKILL_D("force/recover")->exert(me, me)&&me->query_skill("force")>120)
		{
			if( (int)me->query("qi") < exercise_cost)
			{
				tell_object(me,"��Ѫ���㣬��Ϣ�С�����\n");
				call_out("auto_dazuo",10,me,exercise_cost);
			}
			else
			{
				call_out("auto_dazuo",1,me,exercise_cost);
			}
		}
		else
		{
			tell_object(me,"��Ѫ���㣬��Ϣ�С�����\n");
			call_out("auto_dazuo",10,me,exercise_cost);
		}
	}
	else
	{
		tell_object(me,"�й��У���������������������\n");
		tell_object(me,ZJFORCECMD("dazuo "+exercise_cost));
	}
}

int exercising(object me)
{
	int finish;
	int neili_temp,skill_temp_point;
	int exercise_cost = (int)me->query_temp("exercise_cost");
	mapping map_temp;
	object where=environment(me);
	map_temp = me->query_skill_map();  
      if (!interactive(me)) return 0;
	if (exercise_cost < 1)
		return 0;
	if (! me->query_temp("dazuo/step"))
		me->set_temp("dazuo/step", 1);

	if (! living(me))
	{
		me->set_temp("pending/exercise", 0);
		me->delete_temp("dazuo/step");
		return 0;
	}
	finish = 0;

	switch (me->query_temp("dazuo/step"))
      {
      case 1:
		write(YEL"һ������������"+HIR"���ٻ�Ѩ��"+NOR+YEL"�㿪ʼ��תС����......"+NOR"\n");
      	break; 
      case 2:
		write(YEL"��������"+HIW"��ӡ��Ѩ��"+NOR+YEL"���ֻ����Ŀ�ʼ����......"+NOR"\n");
      	break;
      case 3:
		write(YEL"��������"+HIG"��̴��Ѩ��"+NOR+YEL"�����������ֻ���������......"+NOR"\n");
      	break;
      case 4:
		write(YEL"��Ŭ������ů����������"+HIR"���ٻ�Ѩ��"+YEL+"����ʱ����һ��"+NOR"\n");
      	break;
 	default:
		finish = 1;
		break;
	}

	if(!finish)
	{
		me->add_temp("dazuo/step", 1);
		return 1;
	}
	neili_temp=((int)me->query_skill(map_temp["force"]))/5+random(9)+exercise_cost;  //�ڹ��ȼ�/5+�漴ϵ��+����=ʵ��Ч��
	skill_temp_point=random(8)+8; 
	if(where->query("xuanbing"))
 		me->add("qi", (int)exercise_cost/3);
	if(where->query("hanyuchuang"))
		me->add("qi", (int)exercise_cost/2);   
	me->add("qi", -exercise_cost);
	me->set_temp("pending/exercise", 0);
	tell_object(me,"�����������۾����������˿�����վ��������\n"
			+HIW"��о��ڹ��־����ˣ�\n"
			+HIR"��������"NOR" "+HIG"+"+neili_temp+NOR+HIR	+"  ��"+to_chinese(map_temp["force"])+"��"NOR" "HIG"exp +"+skill_temp_point+NOR"\n");
	me->improve_skill(map_temp["force"],skill_temp_point);
	me->add("neili", neili_temp);
	if(me->query_temp("pending/auto_dazuo"))
		call_out("auto_dazuo",1,me,exercise_cost);
	if ((int)me->query("neili") < (int)me->query("max_neili") * 2)
		return 0;
	else
	{
/*
if ( me->query_neili_limit()-100 > (me->query_skill("force", 1) + me->query_skill("force")/5) * 10)
     neili_limit1=me->query_neili_limit()-100;
else neili_limit1=(me->query_skill("force", 1) + me->query_skill("force")/5) * 10;
*/
		if ((int)me->query("max_neili") >= me->query_neili_limit() )
		{
			write("���������Ϊ�ƺ��Ѿ��ﵽ��ƿ����\n");
			me->set("neili", (int)me->query("max_neili"));
			return 0;
		} 
		else if ((int)me->query_skill("linji-zhuang",1) == 100 &&(int)me->query("max_neili") == 500)
		{
			me->add("max_neili", 100);
			me->set("neili", (int)me->query("max_neili"));
			write("��ֻ�����ﴦһ������ӿ��ȫ������˵����������øо�����֪���������Ѿ��������ټ�ʮ��ׯ������ׯ��\n");
			return 0;
		}
		else if ((int)me->query_skill("linji-zhuang",1) == 300 &&(int)me->query("max_neili") == 1000)
		{
			me->add("max_neili", 200);
			me->set("neili", (int)me->query("max_neili"));
			write("��ֻ�������Ϣ�α�����ȫ���·����������֮�䣬���Ѿ��ڻ��ͨ���ټ�ʮ��ׯ�ĵ���ׯ���Ѿ�����(yun tiandi)�ˡ�\n");
			return 0;
		}
		else
		{
			me->add("max_neili", 1);
			me->set("neili", (int)me->query("max_neili"));
			write(""WHT"�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m"NOR"\n");
			write(HIR"��ϲ:"+NOR+"���"+HIG"���������ޡ�"+NOR+"�����ˣ�"NOR"\n");
			write(""WHT"�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i"NOR"\n");
			return 0;
		}
	}
}
int halt_exercise(object me)
{
	if ((int)me->query("neili") > (int)me->query("max_neili") * 2)
		me->set("neili", (int)me->query("max_neili") * 2);
	me->delete_temp("dazuo/step");
	me->set_temp("pending/exercise", 0);
	message_vision("$N����Ϣѹ�ص�������������۾���\n", me);
	return 1;
}
int help(object me)
{
	write(@HELP
ָ���ʽ : exercise [<�ķѡ���������> ������� 10]
�����������������ڵ����ڸ�����������������ѵ�����弡���������
��������������������������ʽ����������������
HELP
	);
	return 1;
}
