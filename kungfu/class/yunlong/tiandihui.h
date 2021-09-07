// tiandihui.h for join tiandihui

#include <ansi.h>

int do_join(string arg)
{
	object me, ob, obj ;
	string tang;
	mapping party;

	me = this_object () ;
	ob = this_player () ;

	if (! arg || arg != "tiandihui")
		return notify_fail("��Ҫ����ʲô��֯��\n"); 

	if ((int)ob->query("weiwang") < 20)
	{
		message_vision(HIR "$N" HIR "��$n" HIR "��������᣿��Ľ���"
			       "����̫�ͣ���ػᶼ�Ǹ�����Ϊ�ĺú���"NOR"\n",
			       me, ob);
		return 1;
	}

	if ((int)ob->query("shen") < 0)
	{
		message_vision(HIR "$N" HIR "��$n" HIR "��ŭ����������᣿"
			       "һ������Ǹ��󺺼�! "NOR"\n", me, ob);
		set_leader(this_player());
		remove_call_out("kill_ob");
		me->kill_ob(ob); 
		return 1;
	}

	if (ob->query("party") &&
	    ob->query("party/party_name") !="��ػ�")
	{
		message_vision("$Nҡҡͷ����$n˵�������Ѿ�����������"
			       "���ˣ�������������ػᡣ\n", me, ob);
		return 1;
	}

	if (ob->query("party/party_name") == "��ػ�")
	{
		message_vision("$Nҡҡͷ����$n˵�������Ѿ�����"
			       "��ػ�����ˡ�\n",me,ob);
		return 1;
	}

	switch (random(10))
	{
		case 0 : tang=HIG"��ľ��"; break;
		case 1 : tang=HIG"�����"; break;  //������
		case 2 : tang=HIW"������"; break;
		case 3 : tang=BLU"��ˮ��"; break;
		case 4 : tang=YEL"������"; break;
		case 5 : tang=HIG"������"; break;  //�̵���
		case 6 : tang=HIG"��˳��"; break;  //�����
		case 7 : tang=HIW"�Һ���"; break;  //����
		case 8 : tang=BLU"��̫��"; break;
		default: tang=YEL"�껯��"; break;  //��
	}
	party = allocate_mapping(5);
	party["party_name"] = "��ػ�";
	party["rank"] = tang + NOR"����";
	party["level_tdh"] = 1;
	party["tasks"] = 0;
	party["enter_time"] = time();
	ob->set("party", party);

	command("smile");
	message_vision("$N��$n˵���������ʱ��" + tang + NOR +
		       "Ч���ɣ�\n", me, ob);
	if (ob->query("weiwang") < 50)
	{
		ob->set("weiwang", 50);
		message_vision(HIC "$N�Ľ�����������ˣ�"NOR"\n", this_player());
		return 1;	
	}
	return 1;
}
