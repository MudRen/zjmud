#include <ansi.h>
inherit NPC;

int do_stop();
int do_liandan();
string ask_me();
string ask_yinzhen();

void create()
{
	set_name("Ҧ��", ({"yao chun", "yao", "chun"}));
	set("gender", "����");
	set("age", 56);
	set("title", HIG "�ش���" NOR);
	set("nickname",HIR "������ҽ" NOR);
	set("long",
		"����Ǿ��ǻش���ҩ�̵ĵ�����ҽҦ������ĸ�"
		"�ݣ���ò���������ػ����촨�����ˣ�����"
		"��ҽ�Σ����˼�����ҽ�����ö̴�Ҳ��һ����\n");
	set("attitude", "heroism");
	set("shen_type",1);
	set("str", 32);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("qi", 20000);
	set("max_qi", 20000);
	set("jing", 1600);
	set("max_jing", 1600);
	set("neili", 20000);
	set("max_neili", 20000);

	set("combat_exp", 10000000);
	set("score", 300000);
	 set("skill_yaochun", 1);
	set_skill("medical", 150);
	set_skill("zhenjiu-shu", 150);
	set_skill("liandan-shu", 150);
	set_skill("literate", 150);

	map_skill("medical", "bencao-shuli");

	set("inquiry", ([
		"���촨"  :  "���Ϻ�������Ҹ�ҽ�εģ���ô��Ҳ֪����\n",
		"����"    : (:do_liandan:),
		"ҩ��"    :  "ȥ���ҵ�Сͯ��������㴦��\n",
		"ҽ��"    : (: ask_me :),
		"���"    : (: ask_yinzhen :),
		"ֹͣ����"    : (: do_stop :),
	]) );

	setup();

}

void init()
{
	::init();
	remove_call_out("greeting");
	call_out("greeting", 1, this_player());
}

int do_stop()
{
	object me = this_player();

	if (me->query("combat_exp") < 2000000) {
                command("say �㻹û�п�ʼ���������ҽ�����");
                return 1;
        }
      me->delete_temp("liandan");
      me->delete_temp("caiyao");
      command("sigh "+me->query("id"));
      command("say "+me->name()+"��Ҳ����������"+me->name()+"�ˣ���Ȼ��ˣ��Ǿ������°ɡ�");
      return 1;

}

int do_liandan()
{
	int exp, pot;
	object me = this_player();

	if (me->query("combat_exp") < 2000000) {
                command("say ���ʵս����̫��,����������ʲô�õ��ɣ�");
                return 1;
        }

	if (me->query_temp("liandan"))
	{
		if (me->query_temp("liandan") < 4)
		{
			command("say ����Ҫȥ��������ô��������ţ�\n");
	            call_out("do_lian2", 5, me);
			return 1;
		}
		message_vision(CYN "Ҧ����$N" CYN "΢Ц���������Ǹ��������ԵĹ��̣����ܳɹ����ܲ���"NOR"\n", me);

		exp = 40 + random(20);
		pot = exp - random(20);

		me->add("combat_exp", exp);
		pot=me->improve_potential(pot);
		tell_object(me, HIC "������˵�" + chinese_number(me->query("over_quest/liandan_quest", 1)+1) + "��������"NOR"\n" );
		tell_object(me, HIC "������" + chinese_number(exp) +	"�㾭���" + chinese_number(pot) + "��Ǳ�ܡ�"NOR"\n" );

		me->delete_temp("liandan");
		me->add("over_quest/liandan_quest", 1);

	      call_out("do_lian1", 5, me);
		return 1;
	} else
	{
		message_vision(CYN "Ҧ����$N" CYN "���˵�ͷ��˵���������ǿ����˵Ķ�����Ϊ���Ĳ������²��ɣ���ȥ��ͯ��ѯ�ʡ�" HIG "ҩ��" NOR + CYN "���ɡ�"NOR"\n", me);
		me->set_temp("liandan", 1);

	      call_out("do_lian2", 5, me);
		return 1;
	}
}


void do_lian1(object me)
{
	if (! objectp(me))
		return;

      tell_object(me,ZJFORCECMD("ask yao chun about ����"));

}

void do_lian2(object me)
{
	if (! objectp(me))
		return;

      tell_object(me,ZJFORCECMD("s")+ZJFORCECMD("ask xiao tong about ��ҩ"));

}


string ask_me() 
{
	object me;

	me = this_player();

	if (me->query("can_learn_medical/yaochun") == 1)
		return "�Ҳ��Ǵ�Ӧ����������������ô��ô���£�";

	if (me->query("shen") < -10000)
		return "������ħͷ����ȥɱ�˶��������ִ����ˡ�";

	if (me->query("over_quest/liandan_quest") < 100 )
		return "�����ɣ����Ȱ��������ٴΣ��ĳ�֮ʱ����Ȼ�ᴫ�ڸ��㡣";

	if (me->query("shen") < 0)
		return "�������������ò������������֮������Ȼ�ᴫ�ڸ��㡣";

	me->set("can_learn_medical/yaochun", 1);
	       return "��Ȼ������������ѧҽ֮�����Ҿͳ�ȫ��ȫ��ɡ�"; 
}

int recognize_apprentice(object me, string skill)
{
	if (me->query("shen") < -10000)
	{
		command("say ���ҹ������Ҳ��ᴫ���κμ��ܸ�������ħͷ��");
		return -1;
	}

	if ( ! me->query("can_learn_medical/yaochun") )
	{
		command("say �ҵ�ҽ�������ǲ����״��ڵġ�");
		return -1;
	}

	if (skill == "literate")
	{
		command("say ����д���Լ�ȥ�ҽ�������ѧȥ��");
		return -1;
	}

	if (skill != "medical" &&
	    skill != "zhenjiu-shu")
	{
		command("say ��ֻ�ܴ��ڻ���ҽ�����������");
		return -1;
	}

	return 1;
}

string ask_yinzhen()
{
	mapping fam; 
	object ob;
	object me = this_player();

	if (me->query("shen") < -0)
		return "���߰ɣ��ҵ�����ɲ�������������ˡ�";

	if ((int)me->query_skill("zhenjiu-shu", 1) < 60)
		return "�������������죬��������Ū���������ġ�";

	if (present("yin zhen", this_player()))
		return "�����ϲ��ǻ���һ����";

	ob = new("/d/beijing/obj/yinzhen");
	ob->move(me);

	message_vision(HIW "\nҦ����������������һ�����룬�ݸ���$N" HIW "��"NOR"\n", me);
		return "����������������ģ��úõ�������Ϊ���β��ɡ�";
}

