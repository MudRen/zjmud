// girl for user

#include <ansi.h>

inherit NPC;

#define DEFAULT_NAMR    "Ѿ��"

void   set_owner(object owner);
string description();

void create()
{
	set_name(DEFAULT_NAMR, ({ "ya huan" }));
	set("age", 12 + random(8));
	set("attitude", "friendly");
	set("gender", "Ů��");

	set("max_qi", 1000);
	set("max_jing", 500);

	set("per", 20);
	set("str", 15);

	set("long", "����һ��СѾ�ߡ�\n" + description());

	setup();

	carry_object("/clone/cloth/female" + (random(8) + 1) + "-cloth.c")->wear();	
	carry_object("/clone/cloth/female-shoe.c")->wear();

	if (clonep()) keep_heart_beat();
}

void set_owner(object owner)
{
	object *obs;

	set_temp("owner", owner);
	obs = owner->query_temp("hire");
	if (arrayp(obs))
	{
		obs = obs - ({ 0 }) + ({ this_object() });
		owner->set_temp("hire", obs);
	} else
		owner->set_temp("hire", ({ this_object() }));

	if (environment() &&
	    environment(owner) == environment())
	{
		// ��������
		message_vision("$N����$n�����\n", this_object(), owner);
		set_leader(owner);
	}

	set("title", owner->name(1) + "��Ѿ��");
}

string long()
{
	object owner;
	string msg;

	if (! objectp(owner = query_temp("owner")))
		return ::long();

	msg = short() +
	      "\n����" + owner->name(1) + "(" + owner->query("id") +
	      ")������Ѿ�ߡ�\n" + description();
	return msg;
}

int do_name(string arg)
{
	string mid;
	string msg;

	if (this_player() != query_temp("owner"))
		return 0;

	if (! stringp(arg))
		return notify_fail("��Ҫ��ʲô���֣�\n");

	if (sscanf(arg, "%s %s", arg, mid) != 2)
		return notify_fail("������ʲô����(name �������� Ӣ�Ĵ���)��\n");

	if (strlen(mid) < 3)
		return notify_fail("�����Ӣ�Ĵ����õ�Ҳ̫���ˡ�\n");

	if (strlen(mid) > 8)
		return notify_fail("�����Ӣ�Ĵ����õ�Ҳ̫���ˡ�\n");

	if (! is_legal_id(mid))
		return notify_fail("Ӣ�Ĵ��ű���ʹ��Ӣ��Сд��ĸ��\n");

	if (! is_chinese(arg))
		return notify_fail("���������������֡�\n");

	if (strlen(arg) < 4)
		return notify_fail("�������̫���ˡ�\n");

	if (strlen(arg) > 8)
		return notify_fail("������������Ҳ̫���ˡ�\n");

	if (arg == name())
		return notify_fail("�˼����ڲ����ǽ��������ô��\n");

	if (arg == this_player()->name(1))
		return notify_fail("����ôȡһ�����Լ�һ�������֣�\n");

	if (msg = NAME_D->invalid_new_name(arg))
	{
		write(msg);
		return 1;
	}

	if (query("name") != DEFAULT_NAMR)
		return notify_fail("�˼��Ѿ��������ˣ���ͱ�����ˡ�\n");

	message_vision("$N����һ�������$n�����������ɣ��Ժ���ͽ�" +
		       arg + "���ˡ���\n$n���ֵ�������ѽ��ѽ������" +
		       RANK_D->query_respect(this_player()) +  "֮" +
		       "�ԣ��Ժ��Ҿͽ�" + arg + "�ˡ���\n",
		       this_player(), this_object());
	set_name(arg, ({ mid }));
	remove_action("do_name", "name");

	return 1;
}

int do_nick(string arg)
{
	if (! arg)
		return notify_fail("��Ҫ��" + name() + "һ��ʲô�ǳƣ�\n");

	if (arg == "none")
	{
		delete("nickname");
		write("���" + name() + "�Ĵº�ȡ���ˡ�\n");
		return 1;
	}

	if (strlen(arg) > 80)
		return notify_fail("��Ĵº�ռ�õ���Դ���࣬���������á�\n");

	arg = replace_string(arg, "$BLK$", BLK);
	arg = replace_string(arg, "$RED$", RED);
	arg = replace_string(arg, "$GRN$", GRN);
	arg = replace_string(arg, "$YEL$", YEL);
	arg = replace_string(arg, "$BLU$", BLU);
	arg = replace_string(arg, "$MAG$", MAG);
	arg = replace_string(arg, "$CYN$", CYN);
	arg = replace_string(arg, "$WHT$", WHT);
	arg = replace_string(arg, "$HIR$", HIR);
	arg = replace_string(arg, "$HIG$", HIG);
	arg = replace_string(arg, "$HIY$", HIY);
	arg = replace_string(arg, "$HIB$", HIB);
	arg = replace_string(arg, "$HIM$", HIM);
	arg = replace_string(arg, "$HIC$", HIC);
	arg = replace_string(arg, "$HIW$", HIW);
	arg = replace_string(arg, "$NOR$", NOR);

	if (strlen(filter_color(arg)) > 30)
		return notify_fail("���������º�̫���ˣ���һ����һ��ġ�����һ��ġ�\n");

	set("nickname", arg + NOR);
	write("��Ϊ" + name() + "ѡ��һ���ºš�\n");
	return 1;
}

mixed accept_ask(object who, string topic)
{
	object me;
	object owner;
	object *obs;
	object cob;
	string nick;

	me = this_object();

	if (! objectp(owner = query_temp("owner")))
		message_vision("$N������Χ����Щ��ɬ��û�лش�$n�Ļ���\n",
			       me, who);

	if (topic == "name" || topic == "����" || topic == "����")
	{
		// ѯ������
		if (who != owner)
			return "����������ָ�ʲô�����ǻ��˻��Ǻ��ˣ�";

		if (name() == DEFAULT_NAMR)
		{
			remove_action("do_name", "name");
			add_action("do_name", "name");
			return "�����ڻ�û�������أ��������(name)һ���ò��ã�";
		}

		return "�ҵ����ֽ�" + name() + "ѽ���㲻�ǵ���ô��";
	}

	if (topic == "nick" || topic == "�ǳ�" || topic == "�º�")
	{
		// ѯ���ǳ�
		nick = query("nickname");
		if (who != owner)
		{
			if (! stringp(nick) || strlen(nick) < 1)
				return "��û��ʲô�º�Ŷ��";

			return "��... �˼Ҷ�����" + nick + "��";
		}

		remove_action("do_nick", "snick");
		add_action("do_nick", "snick");

		if (! stringp(nick))
			return "������û�дº�ѽ����Ҫ������(snick)һ����";

		return "�����ڽ�" + nick + NOR CYN "ѽ���������һ�(snick)һ��ô��";
	}

	if (topic == owner->name(1) || topic == owner->query("id"))
	{
		if (who == owner)
		{
			message_vision("$N����������һЦ����$n��������"
				       "�Ͳ�Ҫ���ҿ���������\n", me, who);
			return 1;
		}

		return "��������ѽ������" + gender_pronoun(owner->query("gender")) +
		       "��ʲô����ô��";
	}

	if (topic == name() || topic == query("id"))
	{
		if (who == owner)
			return "������������ء�";
		else

			return "������������ô�����ʹ��ҵ����˰ɡ�";
	}

	if (who != owner)
	{
		// �������Ƿ��޹�ϵ
		if (who->query("id") == owner->query("couple/id"))
		{
			message_vision("$Nӯӯ����$n����һ���򸣡�\n",
				       me, who);	
			return 1;
		}

		// �������ǽ���ֵܹ�ϵ
		if (who->is_brother(owner))
		{
			message_vision("$N����һЦ��������" +
				       RANK_D->query_respect(who) +
				       "��ҪȡЦ��������\n",
				       me, who);
			return 1;
		}

		// İ����
		switch (random(5))
		{
		case 0:
			message_vision("$Nգ�Ŵ��۾����޹�������$n��һ��"
				       "������а�����ӡ�\n", me, who);
			break;
		case 1:
			message_vision("$N����һЦ��û�д���$n��\n", me, who);
			break;
		case 2:
			message_vision("$N������" + owner->name(1) +
				       "˵���������Һ�����˵�������滵��"
				       "�ɶ��ˡ���\n", me, who);
			break;
		case 3:
			message_vision("$N����������$n�������Ҳ����µģ�"
				       "������������\n", me, who);
			break;
		default:
			message_vision("$N����$n�Ļ���ʲôҲû��˵��ֻ��"
				       "����˫�峺��Ŀ��ɨ��$nһ�ۡ�\n", me, who);
			break;
		}

		return 1;
	}

	if (topic == "all")
	{
		string *names;
		int count;

		obs = obs = all_inventory(me);
		obs = filter_array(obs, (: ! $1->query("equipped") :));
		if (! sizeof(obs))
			return "����������ɶҲû��ѽ��";

		count = 0;
		names = allocate(sizeof(obs));
		foreach (cob in obs)
			if (! count || member_array(cob->name(), names) == -1)
				names[count++] = cob->name();
		tell_object(who, sort_string(name() + "���ĵظ����㣺�����������ڴ���" +
					     implode(names, "��") + "�ء���\n", 60));
		return "������Ҫ��ʲô��";
	}

	// �쿴ѯ�ʵ��Ƿ�������Я������Ʒ
	obs = all_inventory(me);
	foreach (cob in obs)
	{
		if (cob->query("equipped"))
			continue;

		if (filter_color(cob->name(1)) != topic && ! cob->id(topic))
			continue;

		// �ҵ���
		message_vision("$N��������һ�£�������ء���˵���ͳ�" +
			       cob->name() + "�ݸ�$n��\n", me, who);
		if (! cob->move(who))
			message_vision("����$n���ϴ��Ķ���̫�࣬û�ܽ�ס$N��" +
				       cob->name() + "��\n", me, who);
		return 1;
	}

	switch (random(3))
	{
	case 0:
		return "��˵ʲô����û�����ѽ��";
	case 1:
		return "Ŷ��������Ҫ������Ҫʲô�أ�";
	default:
		return "��...��һ�£���˵ʲô��";
	}
}

int accept_object(object who, object ob)
{
	object me;
	object owner;

	me = this_object();
	if (! objectp(owner = query_temp("owner")))
		return 0;

	if ((who != owner) && who->query("couple/id") != owner->query("id"))
	{
		message_vision("$N��æҡͷ���������ҿɲ���Ҫ���Ķ�������Ȼ" +
			       (owner ? owner->name() : "����") +"�����ҵġ���\n", me);
		return 0;
	}

	if (ob->is_character() && query("can_speak"))
	{
		message_vision("$N����ü��Ϊ�ѵ�������...���Ҳ�������ѽ����\n", me);
		return 0;
	}

	if (ob->is_corpse())
	{
		message_vision("$N��ѽ����һ���������⣬���ҲҪ���ã���\n", me);
		return 0;
	}

	message_vision("$N������" + name() + "�������" + ob->name() +
		       "�պ��ˡ� ��\n", owner);
	if (ob->move(me))
	{
		message_vision("$N���ͷ�������" + ob->name() +
			       "���˹�ȥ�����ȵ��պá�\n", me);
		return -1;
	}

	message_vision("$N�����ء����������... ���Ѿ��ò����ˡ���\n", me);
	return -1;
}

int accept_ansuan(object ob)
{
	return notify_fail("��ô�崿��С����㲻�������֡�\n");
}

int accept_touxi(object ob)
{
	message_vision("Ȼ��$N�����ǹ�������������崿�������������֡�\n", ob);
	return -1;
}

int accept_fight(object ob)
{
	message_vision("$N����һ������������������$n��\n",
		       this_object(), ob);
	return -1;
}

int accept_hit(object ob)
{
	message_vision("$N����һ������������������$n����$n���в��ɵ�һ��\n",
		       this_object(), ob);
	return -1;
}

int accept_kill(object ob)
{
	object me;
	object *obs;

	me = this_object();
	if (ob == query_temp("owner"))
	{
		message_vision("$N���һ�ˣ�ί���ĺ�������Ϊʲô��Ϊʲô"
			       "Ҫ�������ң�\n$n����һ��û�����֣�����"
			       "���Ŀ���$N�ܵ��ˡ�\n", me, ob);
		obs = all_inventory(me);
		obs = filter_array(obs, (: ! $1->query("equipped") :));
		if (sizeof(obs))
		{
			message_vision("$N�����ϵĶ�������һ��...\n", me);
			obs->move(environment());
		}
		destruct(me);
		return -1;
	}

	message_vision("$N��æ�����ȥ��ί���ĳ�$n����������λ" +
		       RANK_D->query_respect(ob) +"�����ϴ����˰ɣ���\n",
		       me, ob);
	return -1;
}

void relay_emote(object me, string arg)
{
	string my_id;
	object owner;

	if (! objectp(owner = query_temp("owner")))
		return;

	my_id = me->query("id");
	if (me == owner || my_id == owner->query("couple/id"))

	switch (random(5))
	{
	case 0: command("shy");	 return;
	case 1: command("shzi");	return;
	case 2: command("xixi");	return;
	case 3: command("@@ " + my_id); return;
	default:command("angry");       return;
	}

	if (me->query_temp("last_emote_with_girl") == time())
	{
		if (me->add_temp("last_emote_times", 1) > 2)
		{
			message_vision(HIR "$N" HIR "��Цһ��������һ�Ž�$n"
				       HIR "�ߵ��ڵأ�\n", this_object(), me);
			me->receive_damage("qi", 50, this_object());
			me->receive_damage("jing", 40, this_object());
			return;
		}
	} else
	{
		// reset count
		me->set_temp("last_emote_with_girl", time());
		me->delete_temp("last_emote_times");
	}

	arg = replace_string(arg, "1", "");
	arg = replace_string(arg, "2", "");
	arg = replace_string(arg, "3", "");
	arg = replace_string(arg, "4", "");
	arg = replace_string(arg, "5", "");
	switch (arg)
	{
	case "kiss":    command("rascal " + my_id);     break;
	case "hug":     command("escape " + my_id);     break;
	case "kok":     command("wuwu " + my_id);       break;
	case "kick":    command("killair " + my_id);    break;
	case "kickfly": command("papa");		break;
	case "wuwu":    command("comfort " + my_id);    break;
	case "comfort": command("say �Һܺ�ѽ��");      break;
	case "killair": command("heng " + my_id);       break;
	case "slap":    command("angry " + my_id);      break;
	case "zhen":    command("pain");		break;
	case "poor":    command("say ��ſ����ء�");    break;
	case "xbc":     command("say �����С�ײ��ء�");break;
	case "flop":    command("standup");	     break;
	case "tang":    command("say ��Ҫ...�Ҳ�Ҫ��"); break;
	case "faint":   command("standup " + my_id);    break;
	case "break":   command("inn " + my_id);	break;
	case "cat":     command("xixi " + my_id);       break;
	case "lean":    command("shy " + my_id);	break;
	case "tnnd":    command("say �����˺ö���Ŷ��");break;
	case "wave":    command("say ����߰ɡ�");      break;
	case "shrug":   command("? " + my_id);	  break;
	case "xixi":    command("say ��ò�������");    break;
	case "laugh":   command("say ��ô��һ��...ɵ�ӣ�");     break;
	case "inn":     command("nopretend " + my_id);  break;
	case "sorry":   command("tang " + my_id);       break;
	case "chaxie":  command("pat " + my_id);	break;
	case "pat":     command("escape");	      break;
	case "smile":   command("smile " + my_id);      break;
	case "shzi":    command("say ��ָɶ��");	break;
	case "haha":
	case "hehe":
	case "hoho":    command("say ɵЦʲô��");      break;
	case "cut":
	case "knife":
	case "club":    command("say " + owner->name(1) + "����ѽ��");	  break;
	case "rascal":  command("say �ҿ������ˡ�");			    break;
	default:	command("say " + owner->name(1) + "���л���ѽ��");      break;
	}
}

void scan()
{
	object me;
	object ob;
	object env;

	me = this_object();

	if (! objectp(ob = query_temp("owner")))
	{
		if (environment())
			message_vision("$N���˿����ܣ����ˡ�\n", me);
		destruct(this_object());
		return;
	}

	env = environment(ob);
	if (environment() == env || ob->is_ghost())
		// �������ڵĵص���ͬ���������˴��ڹ��״̬
		return;

	if (is_busy() || is_fighting() || ! living(this_object()))
		// ����æ
		return;

	if (! sizeof(env->query("exits")) ||
	    environment() && ! sizeof(environment()->query("exits")))
		return;

	if (environment())
		message_vision("$N���������������߿��ˡ�\n", me);

	if (! move(env)) return;

	switch (random(3))
	{
	case 0:
		message_vision("$N�������˹�����վ��$n����ߣ�һ˫�峺"
			       "���۾�Ѳ������Χ��\n", me, ob);
		break;

	case 1:
		message_vision("$N�����������������˹�����վ����$n����"
			       "�ߡ�\n", me, ob);
		break;

	default:
		message_vision("$N���ĵ����˹�����վ��$n��������Ŵ�"
			       "�ҡ�\n", me, ob);
		break;
	}

	set_leader(ob);
}

string description()
{
	int per;

	per = query_per();
	if (per >= 30) return "����������֮ò����ɫ���������޾��ף������˼����ӣ�\n";
	if (per >= 28) return "���������ף����˶��ˡ�������������Ŀ���飬����һЦ������������Ȼ�Ķ���\n";
	if (per >= 26) return "��������֬��üĿ�续���������֣��������ˡ��������Ҽ�������\n";
	if (per >= 24) return "����ɫ����������κ죬�ۺ��ﲨ������Ͷ��֮�䣬ȷ��һ�����ϡ�\n";
	if (per >= 21) return "�����ʸ��ţ���Ŀ毺ã����㲻�Ͼ������ˣ�Ҳ���м�����ɫ��\n";
	return "����òƽƽ�������ù�ȥ��\n";
}

string query_autoload()
{
	string nick;

	return sprintf("%s||%s||%d||%s", query("name"), query("id"), query("per"),
		       stringp(nick = query("nickname")) ? nick : "");
}

void autoload(string para, object owner)
{
	string arg, mid, nick;
	int per;

	if (! stringp(para) || sscanf(para, "%s||%s||%d||%s", arg, mid, per, nick) < 3)
	{
		arg = DEFAULT_NAMR;
		mid = "ya huan";
		per = 20;
	}

	if (stringp(nick) && strlen(nick) > 0)
		set("nickname", nick);

	set("per", per);
	set_name(arg, ({ mid }));
	set_owner(owner);
}

void move_or_destruct()
{
	move(VOID_OB);
}
