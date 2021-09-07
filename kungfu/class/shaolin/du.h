// du.h for fight and apprentice to 3-du

#include "shaolin.h"

mixed ask_whip();

void attempt_apprentice(object ob)
{
	object me  = this_object();
	mapping ob_fam;
	mapping my_fam  = me->query("family");

	string name, new_name;

	if (! permit_recruit(ob))
		return;

	if (! (ob_fam = ob->query("family")) ||
	    ob_fam["family_name"] != "������")
	{
		command("say " + RANK_D->query_respect(ob) +
			"�뱾��������������֪�˻��Ӻ�̸��");
		return;
	}

	if ((string)ob->query("class") != "bonze" &&
	    ob_fam["family_name"] == "������") 
	{
		command("say " + RANK_D->query_respect(ob) +
			"���׼ҵ��ӣ�����������ѧ�ա�");
		return;
	}

	if (ob_fam["generation"] <= my_fam["generation"])
	{
		command("say " + RANK_D->query_respect(ob) +
			"��ƶɮ����ҵ� !");
		return;
	}

	if (ob_fam["generation"] == (my_fam["generation"] + 1))
	{
		command("say " + ob_fam["master_name"] +
			"��ͽ�������ܵ���������ˣ������� !");
		command("recruit " + ob->query("id"));
	}

	if (ob_fam["generation"] == (my_fam["generation"] + 2))
	{
		if (ob->query_temp("valid_in_fumoquan") == 1)
		{
			if (ob->query_skill("dodge",1) >= 120 &&
			    ob->query_skill("force",1) >= 120 &&
			    ob->query_skill("parry",1) >= 120 &&
			    ob->query_skill("buddhism",1) >= 120)
			{
				command("say ���ܹ���շ�ħȦ����������");
				command("say ƶɮ�ֵ�һ����֮�ţ���ϲ�ɺأ�");

				name = ob->query("name");
				new_name = "��" + name[2..3];
				ob->set("name", new_name);
		
				command("say �ӽ��Ժ���ķ�������" +
					new_name + "��");
				command("recruit " + ob->query("id"));
			}
			else
			command("say ƶɮҪ�յ�������֮�ţ��㻹�ǻ�ȥ"
				"����ʦ��ѧϰ�ɣ�");
		} else
		{
			command("say " + RANK_D->query_respect(ob) +
				"��û�ܹ���շ�ħȦ���Ҳ������㡣");
			return;
		}
	}
	return;
}

void setup()
{
	object ob;
	int count;

	set("inquiry/����",   (: ask_whip :));
	set("inquiry/hei suo", (: ask_whip :));
	set("inquiry/black whip", (: ask_whip :));
	set("inquiry/����", "�������е��ǣ����Լ�ȥ�Һ��ʵİɡ�");
	set("inquiry/whip", "�������е��ǣ����Լ�ȥ�Һ��ʵİɡ�");

	::setup();

	ob = carry_object("/d/shaolin/obj/changbian");

	if (clonep())
	{
		count = sizeof(filter_array(children("/d/shaolin/obj/heisuo"), (: clonep :)));
		if (count < 3) ob = carry_object("/d/shaolin/obj/heisuo");
	}

	ob->wield();
}

mixed ask_whip()
{
	object me;
	object ob;

	me = this_player();
	if (me->query("family/family_name") != query("family/family_name"))
		return "�����������ģ�������������ʲô��";

	if (me->query("combat_exp") < 400000)
		return "�����΢ĩ���򣬿ɲ�Ҫ�������ǵĻ��������ȥ������";

	if (time() - me->query_temp("last_ask/blackwhip") < 3600)
		return "���ʲô�����Ǹմ��������ȡ����һ��ô���ѵ���Ū���ˣ�";

	if (me->query("shen") < 30000)
	{
		message_sort("$N�����$n�������ߣ������ҵȽ�����ħ������"
			     "���㿴��ȥҲ������������֮�ˡ��������ֵ��ӱ�"
			     "Ӧ�ȱ�Ϊ������Ҳ�ֲ����㣬ȥ�ɣ���\n",
			     this_object(), me);
		return 1;
	}

	ob = present("hei suo", this_object());
	if (! objectp(ob))
		return "������Ѿ�û�к����ˣ���ȥ�����Լ��ҳ��ֵı����ɡ�";

	message_vision("$N���˿�$n�������еľ����������ݸ�$n��\n",
		       this_object(), me);
	ob->move(me, 1);

	if (objectp(ob = present("bian", this_object())))
		ob->wield();

	me->set_temp("last_ask/blackwhip", time());

	return "�ܺã����Ȼ�����ħ������ȻӦ������һ��֮����";
}
