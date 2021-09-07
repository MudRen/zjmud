// itemd.c

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <command.h>

void create() { seteuid(getuid()); }

// ����������͸����Ʒ�б���������Ʒ��base_name
mapping imbue_list = ([
	"feicui lan":"�����",
	"puti zi":"������",
	"ling zhi":"ǧ����֥",
	"xian dan":"�����ɵ�",
	"xisui dan":"ϴ�赤",
	"shenli wan":"������",
	"huohong xiandan":"����ɵ�",
	"jiuzhuan jindan":"��ת��",
	"magic water":"������¶",
	"fushou gao":"���ٸ�",
]);

// ����Ĵ�����������ޣ����ÿ��IMBUE�Ժ�ȡ0-IMBUE���������
// �����������ֵ����IMBUE���ճɹ���
#define RANDOM_IMBUE_OK	 80

// ÿ�ν�����Ҫʥ���Ĵ���
#define SAN_PER_IMBUE	   5

// ɱ�����Ժ�Ľ���
void killer_reward(object me, object victim, object item)
{
	int exp;
	mapping o;
	string my_id;

	if (! me || ! victim)
		return;

	if (! victim->query("can_speak"))
		return;

	// record for this weapon
	if (victim->is_not_bad())  item->add("combat/WPK_NOTBAD", 1);
	if (victim->is_not_good()) item->add("combat/WPK_NOTGOOD", 1);
	if (victim->is_good())     item->add("combat/WPK_GOOD", 1);
	if (victim->is_bad())      item->add("combat/WPK_BAD", 1);

	if (userp(victim))
		item->add("combat/PKS", 1);
	else
		item->add("combat/MKS", 1);

	exp = (int)victim->query("combat_exp");
	if (exp < 10000 || me->query("combat_exp") < exp * 4 / 5 || exp < item->level_now()*300000 || item->item_owner()!=me->query("id"))
		return;

	if(random(2))
		return;

	exp /= 10000;
	if (exp > 250) exp = 100 + (exp - 250) / 16; 
	else if (exp > 50) exp = 50 + (exp - 50) / 4;
	if (exp>100) exp = 100;
	my_id = me->query("id");
	o = item->query("owner");
	if (! o) o = ([ ]);
	if (! undefinedp(o[my_id]) || sizeof(o) < 12)
		o[my_id] += exp;
	else
	{
		int i;
		int lowest;
		string *ks;

		lowest = 0;
		ks = keys(o);
		for (i = 1; i < sizeof(ks); i++)
			if (o[ks[lowest]] > o[ks[i]])
				lowest = i;
		map_delete(o, ks[lowest]);
		o += ([ my_id : exp ]);
	}
	item->set("owner", o);
}

// �ٻ���Ʒ
int receive_summon(object me, object item)
{
	object env;
	object temp;
	int type;

	if ((env = environment(item)) && env == me)
	{
		tell_object(me, item->name() + "������������"
			    "����ٻ���ʲô����\n");
		return 1;
	}

	if (me->query("neili") < 500)
	{
		tell_object(me, "����ͼ����" + item->name() +
			    "���������Խ��뾳�磬�������������á�\n");
		return 0;
	}
	me->add("neili", -500);

	message_vision(HIW "$N" HIW "ͻȻ���һ��������������"
		       "һץ����Ȼ�����ܲ�������������"NOR"\n", me);

	if (env == environment(me))
	{
		message_vision(HIW "ֻ�����ϵ�" + item->name() +
			       HIW "Ӧ�����𣬷�Ծ��$N" HIW
			       "�����У�"NOR"\n", me);
	} else
	{
		type = random(3);
		if (env)
		{
			if (env->is_character() && environment(env))
					env = environment(env);

			switch (type)
			{
			case 0:
				message("vision", HIW "����д�������������"
					"����Ȼ����������" + item->name() +
					HIW "�ڿն���"
					"��ʧ������"NOR"\n", env);
				break;
			case 1:
				message("vision", HIC "һ�����������"
					"���ֶ���" + item->name() + HIC "��ֻ��" +
					item->name() + HIC "���������ƿն�"
					"�ߡ�"NOR"\n", env);
				break;
			default:
				message("vision", HIY "��Ȼ�������أ���������" +
					item->name() + HIY "�����ʵĶ������£�����һ"
					"�����ת˲������"NOR"\n", env);
				break;
			}

			if (interactive(env = environment(item)))
			{
				tell_object(env, HIM + item->name() +
						 HIM "��Ȼ�����ȥ�ˣ�"NOR"\n");
			}
		}

		switch (type)
		{
		case 0:
			message_vision(HIW "һ��" HIR "����" HIW "��"
				       "���绮�Ƴ��գ�" + item->name() + HIW
				       "�������������$N" HIW "�����У�"NOR"\n", me);
			break;
		case 1:
			message_vision(HIW "һ��" HIY "����" HIW "ɨ��"
				       "��գ�ֻ��" + item->name() + HIW
					"������$N" HIW "�����У�"NOR"\n", me);
			break;
		default:
			message_vision(HIW "ֻ��" + item->name() + HIW "�������죬��"
				       "����ʣ�Ю�ƴ���ͻ����$N"
				       HIW "�����У�"NOR"\n", me);
			break;
		}
	}

	// ȡ��no_get����
	item->delete_temp("stab_by");
	item->delete("no_get");

	item->move(me, 1);
	if (environment(item) != me)
		return 1;

	if (item->query("armor_type"))
	{
		// is armor
		temp = me->query_temp("armor/" + item->query("armor_type"));
		if (temp) temp->unequip();
		WEAR_CMD->do_wear(me, item);
	} else
	if (item->query("skill_type"))
	{
		if (temp = me->query_temp("weapon"))
			temp->unequip();
		if (temp = me->query_temp("secondary_weapon"))
			temp->unequip();
		WIELD_CMD->do_wield(me, item);
	}

	return 1;
}

// ������Ʒ
int hide_anywhere(object me, object item)
{
	if (item->item_owner() != me->query("id"))
		return 0;

	if (me->query("jingli") < 100)
	{
		tell_object(me, "����ͼ��" + item->name() +
			    "��ȥ�����Ǿ������ã����Է�������������\n");
		return 0;
	}
	me->add("jingli", -100);

	message_vision(HIM "$N" HIM "����һ��" + item->name() +
		       HIM "����Ȼ�����ټ���\n", me);
	destruct(item);
	return 1;
}

// ׷Ѱ��Ʒ
int receive_miss(object me, object item)
{
	object env;

	env = environment(item);

	if (me->is_busy())
	{
		write("����æ�����п�����˵��\n");
		return 0;
	}

	if (me->is_fighting())
	{
		write("��������˼���˵�ɣ�\n");
		return 0;
	}

	if (env == environment(me))
	{
		write("�����" + item->name() + "����ɶ��\n");
		return 0;
	}

	if (env == me)
	{
		write("������" + item->name() + "�����˰���Ĵ���\n");
		return 0;
	}

	if (! objectp(env) || userp(env) || environment(env))
	{
		write("����ͼ��Ӧ" + item->name() + "�����Ǹо��ǳ�����ã��\n");
		return 0;
	}

	if (! wizardp(me) && ! env->query("outdoors"))
	{
		write("ڤڤ�����Ӧ��" + item->name() + "�������ƺ����Ե������\n");
		return 0;
	}

	message("vision", me->name() + "������˼������֪��Ҫ��Щʲô��\n",
		environment(me), ({ me }));
	if (me->query("jingli") < 400)
	{
		write("�����" + item->name() + "�ĸо��൱"
		      "Ʈ���������������ã����Ը�Ӧ��\n");
		return 0;
	}

	// ���ľ���
	me->add("jingli", -300 - random(100));
	message_vision(HIM "$N" HIM "���������дʣ�ת˲���һ�����绮"
		       "����$N" HIM "�ݲʺ���ߡ�"NOR"\n", me);
	tell_object(me, "��׷Ѱ" + item->name() + "��ȥ��\n");
	me->move(environment(item));
	message("vision", HIM "һ���ʺ绮����ʣ�" + me->name() +
		HIM "ƮȻ���£��������ɡ�"NOR"\n", environment(me), ({ me }));
	tell_object(me, HIM "��׷Ѱ����" + item->name() +
		    HIM "�����¶ݹ⡣"NOR"\n");
	return 1;
}

// ���ڵ���
int do_stab(object me, object item)
{
	if (! item->is_weapon() && item->query("armor_type") != "hands")
		return notify_fail(item->name() + "Ҳ�ܲ��ڵ��ϣ�\n");

	if (! environment(me)->query("outdoors") &&
	    ! wizardp(me))
		return notify_fail("��������Ūʲô��\n");

	if (! item->is_stay_in_room())
		return notify_fail("��" + item->name() + "�ͱ��������ˡ�\n");

	item->set("no_get", bind((: call_other, __FILE__, "do_get_item", item :), item));
	item->set_temp("stab_by", me->query("id"));

	message_vision("$N���ֽ�" + item->name() + "������һ�壬��������㶡�һ���졣\n", me);
	item->move(environment(me));
	return 1;
}

// ��ȡ��Ʒʱ���
mixed do_get_item(object item)
{
	object me;

	if (! objectp(me = this_player()))
		return 1;

	if (me->query("id") != item->query_temp("stab_by") &&
	    me->query("id") != item->item_owner())
		return "����ͼ��" + item->name() + "����ȴ�������·�������������һ�㣬�޷�������\n";

	message_vision("$N����һ��" + item->name() + "��ֻ�����ǡ���һ���졣\n", me);
	item->delete_temp("stab_by");
	item->delete("no_get");
	return 0;
}

// �������⹦��
mixed do_touch(object me, object item)
{
	string msg;
	object ob;
	object *obs;
	mapping my;

	if (me->query("id") != item->item_owner())
	{
		message_vision("$N����һ��" + item->name() + "������ֱ������ˣ�ʹ�ô��һ����\n", me);
		me->receive_damage("qi", 50 + random(50));
		return 1;
	}

	if (me->query("jingli") < 100)
	{
		me->set("jingli", 0);
		return notify_fail("�㱧��" + item->name() + "���˰��죬���������дʡ�\n");
	}

	me->add("jingli", -80 - random(20));
	switch (random(3))
	{
	case 0:
		msg = HIM "$N" HIM "����һ��$n"
		      HIM "������������������������"NOR"\n";
		break;
	case 1:
		msg = HIM "$N" HIM "���ḧ��$n"
		      HIM "���п�������ŷ�һ�ף�$n"
		      HIM "�������죬���Ժ�֮��"NOR"\n";
		break;
	default:
		msg = HIM "$N" HIM "ץ��$n"
		      HIM "����˼���á�"NOR"\n";
		break;
	}

	switch (random(3))
	{
	case 0:
		msg += HIM "$n" HIM "��Ȼ����һ���⻪����Ծ��"
		       "��ɢ��ǧ�����롣"NOR"\n";
		break;
	case 1:
		msg += HIM "$n" HIM "����һ�����������Ʋ�����"
		       "ֱ���뵽����ķ���ȥ��"NOR"\n";
		break;
	default:
		msg += HIM "��ʱ$n" HIM "��â���䣬�Ƶ����޷�"
		       "Ŀ�ӣ�ǧ���ɫ������޷���"NOR"\n";
		break;
	}

	msg = replace_string(msg, "$n", item->name());
	message_vision(msg, me);

	if (random(1000) == 1)
	{
		obs = filter_array(all_inventory(environment(me)), (: userp :));
		foreach (ob in obs)
		{
			my = ob->query_entire_dbase();
			my["jing"]   = my["eff_jing"] = my["max_jing"];
			my["qi"]     = my["eff_qi"]   = my["max_qi"];
			my["neili"]  = my["max_neili"];
			my["jingli"] = my["max_jingli"];
			ob->set_temp("nopoison", 1);
		}
		message("vision", HIY "����û�����ͬ����������һ�㣬ů����ģ�˵�����������"NOR"\n", obs);
	} else
	if (me->query("neili") < me->query("max_neili"))
	{
		me->set("neili", me->query("max_neili"));
		tell_object(me, HIY "�����һ�������ӵ���ȽȽ����"NOR"\n");
	}
	return 1;
}

// ʥ����Ʒ
int do_san(object me, object item)
{
	string my_id;
	string ss,*sss;
	int count;
	int san;

	if (! item->query("skill_type") && item->query("armor_type") != "hands")
		// ��װ���ࣿ
		return notify_fail("װ�����ڻ��޷�ʥ��...\n");

	if (me->is_busy())
		return notify_fail("��������æ��\n");

	 if(item->item_owner() != me->query("id"))
		  return notify_fail(item->name() + "����Ҫ�������İɣ�\n");

	// �������ʥ��
	if (item->query("magic/power") > 0)
		return notify_fail("����" + item->name() + "�������Ѿ��õ��˳�ֵķ����ˡ�\n");

	if (item->query("magic/imbue_ok"))
		return notify_fail("����" + item->name() + "��Ǳ���Ѿ�����ھ��ˣ�����ֻ����Ҫ���һ���ںϡ�\n");

	my_id = me->query("id");

	if (item->query("magic/imbue_name")&&item->query("magic/imbue_ob"))
		return notify_fail("����" + item->name() + "�Ѿ�����ֵ�ʥ���ˣ���Ҫ����"+ item->query("magic/imbue_name")+ "�Խ�һ��ĥ����\n");

	if (me->query("neili") < me->query("max_neili") * 9 / 10)
		return notify_fail("�����������������棬����óȻ���ã�\n");

	if (me->query("jingli") < me->query("max_jingli") * 9 / 10)
		return notify_fail("�����ھ������ã�����óȻ���ã�\n");

	if (me->query_skill("force") < 100)
		return notify_fail("����ڹ�����������ʵ������óȻʥ����\n");

	if (me->query("max_neili") < 5000)
		return notify_fail("�㳢������һ���������޷�˳������һ�����죬����ʩչ���������\n");

	if (me->query("max_jingli") < 1000)
		return notify_fail("����ͼ�������þ��������Ǹо�����Ƿȱ��\n");

	message_sort(HIM "$N" HIM "���ḧ��$n" HIM "����ָ�������ϣ�ͬ"
		     "ʱ��ת���������������澭\n����ԴԴ������������ע"
		     "��$n" HIM "��\n����ֻ����������$n" HIM
		     "����Ȼ�������������ܡ�"NOR"\n", me, item);

	if (me->query("max_neili") < me->query_neili_limit() - 200)
	{
		if (random(2) == 1)
		{
			// ����δ������
			message_vision(HIR "$N" HIR "��ɫ��Ȼ���˱䡣"NOR"\n",me);
			tell_object(me, HIC "���Ȼ���õ�����Ϣ��Щ���ҡ�"NOR"\n");
		} else
		{
			message_vision(HIR "$N" HIR "��Ȼ�ƺ�һ��������ɲʱ�����죡"NOR"\n", me);
			tell_object(me, HIC "��е����������������δ�������������������������ڹ�������"NOR"\n");
			tell_object(me, HIC "��Ļ����ڹ��½��ˡ�\n");
			me->set_skill("force", me->query_skill("force", 1) - 10 - random(5));
			return 1;
		}
	}

	// ͳ��IMBUE���Ĵ��������������㱾��MAX_NEILI/JINGLI������
	san = item->query("magic/imbue");

	//me->add("max_neili", -(san + 5));
	me->add("neili", -(san * 10 + 100));
	me->add("max_jingli", -(san * 5));
	me->add("jingli", -(san * 5 + 50));
	me->add("magic_points", -(san * 5 + 50));
	me->start_busy(1);

	if (item->item_owner() == my_id)
	{
		tell_object(me, HIW "������Ƭ�̣�����" + item->name() +  HIW "�ƺ��������ԣ���Ծ���ݣ�����΢΢һЦ��"NOR"\n");
		message("vision", HIW + me->name() + HIW "��Ȼ΢΢һЦ��\n" HIW, environment(me), ({ me }));

		// ѡ��һ����Ҫimbue����Ʒ
		sss=keys(imbue_list);
		ss = sss[random(sizeof(sss))];
		item->set("magic/imbue_ob", ss);
		item->set("magic/imbue_name", imbue_list[ss]);
		tell_object(me,"��������"+ imbue_list[ss] + "����͸һ��" +item->name() + "�ɡ�\n");
	}
	return 1;
}

// ��͸��Ʒ
int do_imbue(object me, object item)
{
	object imbue;

	if (me->is_busy())
		return notify_fail("��������æ��\n");

	 if(item->item_owner() != me->query("id"))
		  return notify_fail(item->name() + "����Ҫ�������İɣ�\n");

	if (item->query("magic/power") > 0)
		return notify_fail("����" + item->name() + "�������Ѿ��õ��˳�ֵķ����ˡ�\n");

	if (item->query("magic/imbue_ok"))
		return notify_fail("����" + item->name() + "��Ǳ���Ѿ�����ھ��ˣ�����ֻ����Ҫ���һ���ںϡ�\n");

	if (!item->query("magic/imbue_name")||!item->query("magic/imbue_ob"))
		return notify_fail("������ȶ�" + item->name() + "���г�ֵ�ʥ�����С�\n");

	if (!objectp(imbue = present(item->query("magic/imbue_ob"),me)))
		return notify_fail("������û��" + item->query("magic/imbue_name") + "����ʲô��͸��\n");
	 
	if (me->query("max_neili") < 6000)
		return notify_fail("�㳢������һ���������޷�˳������һ�����죬����ʩչ���������\n");

	if (me->query("neili") < 4000)
		return notify_fail("��о��������е�Ƿȱ���޷�ʩչ���������\n");

	if (me->query("max_jingli") < 1000)
		return notify_fail("����ͼ�������þ��������Ǹо�����Ƿȱ��\n");
	 
	if (me->query("jingli") < 500)
		return notify_fail("�������޷����о���������¡�\n");

	message_sort(HIM "$N" HIM "����һ����������������һ���˪��ֻ����ס$n" +
		     imbue->name() +
		     HIM "����Ȼ���ڻ������ģ���Ө��͸��$N"
		     HIM "����һ�ӣ���һ����Һ����$n" HIM
		     "�ϣ���ʱ������������������ʣ������˸��"NOR"\n",
		     me, item);
	
	if (me->query("max_neili") < me->query_neili_limit() - 200)
	{
		if (random(2) == 1)
		{
			// ����δ������
			message_vision(HIR "$N" HIR "��ɫ��Ȼ���˱䡣"NOR"\n",me);
			tell_object(me, HIC "���Ȼ���õ�����Ϣ��Щ���ҡ�"NOR"\n");
		} else
		{
			message_vision(HIR "$N" HIR "��Ȼ�ƺ�һ��������ɲʱ�����죡"NOR"\n", me);
			tell_object(me, HIC "��е����������������δ�������������������������ڹ�������"NOR"\n");
			tell_object(me, HIC "��Ļ����ڹ��½��ˡ�\n");
			me->set_skill("force", me->query_skill("force", 1) - 10 - random(5));
			if(imbue->query_amount())
				imbue->add_amount(-1);
			else
				destruct(imbue);
			return 1;
		}
	}
	//me->add("max_neili", -100);
	me->set("neili", 0);
	me->add("max_jingli", -100);
	me->add("jingli", -500);

	tell_object(me, "�㽫" + imbue->name() + "��Ч��������" + item->name() + "��\n");

	item->delete("magic/do_san");
	item->delete("magic/imbue_ob");
	item->delete("magic/imbue_name");
	if(imbue->query_amount())
		imbue->add_amount(-1);
	else
		destruct(imbue);
	me->start_busy(1);

	item->add("magic/imbue", 1);
	if (random(item->query("magic/imbue")) >= RANDOM_IMBUE_OK || me->query("imbue_will_ok"))
	{
		// ��͸���
		tell_object(me, HIG "���Ȼ�������е�" + item->name() + HIG "��һ��ԾԾ���Եĸо����ƺ��ڴ���ʲô��"NOR"\n");
		item->set("magic/imbue_ok", 1);
		me->delete("imbue_will_ok");
	}

	return 1;
}

// ��Ƕ��Ʒ
int do_enchase(object me, object item, object tessera)
{
	int lvl,pw;

	if (me->is_busy())
		return notify_fail("��������æ��\n");

	if(item->item_owner() != me->query("id"))
		  return notify_fail(item->name() + "����Ҫ�������İɣ�\n");

	if (item->query("magic/power") > 0)
		return notify_fail("����" + item->name() + "�������Ѿ��õ��˳�ֵķ����ˡ�\n");

	if (! item->query("magic/imbue_ok"))
		return notify_fail("����" + item->name() + "��Ǳ����û�г�ֵļ�����δ����Ƕ��ʱ��\n");

	if (! tessera->query("can_be_enchased"))
		return notify_fail(tessera->name() + "����û��������Ƕ�ɡ�\n");

	if (! mapp(tessera->query("magic")))
		return notify_fail(tessera->name() + "���ܷ���ħ����û�б�Ҫ��Ƕ��" + item->name() + "���档\n");

	if (me->query_skill("certosina", 1) < (30+item->level_now()*30))
		return notify_fail("����������Ƕ���ջ�������죬����óȻ���֡�\n");

	if (me->query("max_jingli", 1) < 5000)
		return notify_fail("��ľ���̫���ˣ������Լ�Ԧ�ϵ�֮�ۣ��޷���Ƕ��\n");

	pw = tessera->query("magic/power");
	if(pw==30)
	{
		lvl = 1 + rand2(30,3);
	}
	else if(pw==60)
	{
		if(item->level_now()<3)
			return notify_fail(tessera->name() + "��ħ��̫ǿ����" + item->name() + "�ȼ���������ǿ��װ�������õͼ���ʯǿ����\n");
		lvl = 31 + rand2(30,3);
	}
	else if(pw==100)
	{
		lvl = 61 + rand2(40,3);
		if(item->level_now()<5)
			return notify_fail(tessera->name() + "��ħ��̫ǿ����" + item->name() + "�ȼ���������ǿ��װ�������õͼ���ʯǿ����\n");
	}
	else if(pw==150)
	{
		if(item->level_now()<7)
			return notify_fail(tessera->name() + "��ħ��̫ǿ����" + item->name() + "�ȼ���������ǿ��װ�������õͼ���ʯǿ����\n");
		lvl = 101 + rand2(50,3);
	}
	else if(pw==200)
	{
		if(item->level_now()<9)
			return notify_fail(tessera->name() + "��ħ��̫ǿ����" + item->name() + "�ȼ���������ǿ��װ�������õͼ���ʯǿ����\n");
		lvl = 151 + rand2(150,3);
	}
	else 
		lvl = 1;

	if (me->query("balance") < tessera->query("magic/power")*10000)
		return notify_fail("��Ǯׯ���㣬���ܽ��б�ʯ��Ƕ��\n");

	me->add("balance",-tessera->query("magic/power")*10000);
	if (me->query("magic_points")<90000)
		me->set("max_jingli",me->query_jingli_limit());

	message_sort(HIM "��������һ����$N" HIM "��" + tessera->name() + HIM "��Ƕ����$n" HIM "���棬ֻ��$n" HIM "���������Թ���һ������Ĺ�â����"
		     "�����ƽ����˵������ƽ����"NOR"\n", me, item);

	tell_object(me, HIC "�����" + item->name() + HIC "�����˲��������ı仯��"NOR"\n");

	item->set("magic/power", lvl);
	item->set("magic/type", tessera->query("magic/type"));
	item->set("magic/tessera", tessera->name());
	item->save();
	tessera->add_amount(-1);

	// ������Ϣ
	if(lvl>149 && me->query("magic_points")>90000)
		CHANNEL_D->do_channel(this_object(), "rumor","��˵��Ʒ" + item->name() + HIM + "�������˼䡣");
	else if(lvl>99 && me->query("magic_points")>90000)
		CHANNEL_D->do_channel(this_object(), "rumor","��˵" + item->name() + HIM + "��âէ�֣�����������");

	me->start_busy(1);
	return 1;
}

// ǿ��װ��
int do_enhance(object me, object item, object obj)
{
	int exp;
	mapping o;
	string my_id;

	if (! me || ! obj)
		return 0;

	 if(item->item_owner() != me->query("id"))
		  return notify_fail(item->name() + "����Ҫ�������İɣ�\n");

	if(item->level_now()>8)
		return notify_fail("װ��ǿ���Ѵﵽ��ߵȼ�������Ҫ��ǿ���ˣ�\n");
	exp = obj->query("item_exp");

	my_id = me->query("id");
	o = item->query("owner");
	if (! o) o = ([ ]);
	if (! undefinedp(o[my_id]) || sizeof(o) < 12)
		o[my_id] += exp;
	else
	{
		int i;
		int lowest;
		string *ks;

		lowest = 0;
		ks = keys(o);
		for (i = 1; i < sizeof(ks); i++)
			if (o[ks[lowest]] > o[ks[i]])
				lowest = i;
		map_delete(o, ks[lowest]);
		o += ([ my_id : exp ]);
	}
	item->set("owner", o);
	if(item->query("skill_type"))
	{
		item->set("weapon_prop/damage",item->apply_damage());
	}
	else if(item->query("armor_type")=="hands")
	{
		item->set("armor_prop/unarmed_damage",item->apply_damage());
	}
	else if(item->query("armor_type"))
	{
		item->set("armor_prop/armor",item->apply_armor());
	}
	tell_object(me, HIW "һ��΢���Ĺ�â�����������" + item->name() + HIW "�ƺ����������ˡ�"NOR"\n");
	obj->add_amount(-1);
	if(obj)
		tell_object(me, HIM+ZJSIZE(20)+ZJURL("cmds:enhance "+file_name(item)+" with "+file_name(obj))"����ǿ��"NOR"\n");
	return 1;
}

// 10��������������
mixed weapon10lv_hit_ob(object me, object victim, object weapon, int damage_bonus)
{
	mapping magic;
	int jingjia;
	int power, resistance;
	int damage;
	string msg;

	// ����ħ��Ч��
	magic = weapon->query("magic");
	power = magic["power"];
	damage = 0;
	resistance = 0;
	jingjia = me->query("jiajing");
	switch (magic["type"])
	{
	case "lighting":
		// ���繥��
		resistance = victim->query_temp("apply/resistance/lighting");
		damage = (power + jingjia) * 100 / (100 + resistance);
		ITEM_D->receive_damage(me, victim, "qi", damage);
		switch (random(3))
		{
		case 0:
			msg = HIY + weapon->name() + HIY "�ŷ����������������⣬�������죬��$n"HIY"����Ϊ֮���顣"NOR"\n";
			break;
		case 1:
			msg = HIY"һ�����������" + weapon->name() + HIY"���ҫ�۶�Ŀ����$n"HIY"�޷����ӣ������ϡ�"NOR"\n";
			break;
		default:
			msg = HIY"����������������ף�������һ������ֱ�£�" + weapon->name() + HIY"��������������ͷף����$n"HIY"����������"NOR"\n";
			break;
		}
		break;

	case "cold":
		// �䶳����
		resistance = victim->query_temp("apply/resistance/cold");
		damage = (power + jingjia) * 100 / (100 + resistance);
		ITEM_D->receive_damage(me, victim, "qi", damage);
		switch (random(3))
		{
		case 0:
			msg = HIB + weapon->name() + HIB "����һ����ɬ�����⣬��$n" HIB "����������"NOR"\n";
			break;
		case 1:
			msg = HIB "��Ȼ��" + weapon->name() + HIB"���͸��ͨ����һ��������ĺ���ŷ�������$n" HIB "����ֻ��һ�䡣"NOR"\n";
			break;
		default:
			msg = HIB "һ����Ȧ��" + weapon->name() + HIB "�����ɭȻ������$n" HIB "���ܣ���Ȼ��Ϣ��"NOR"\n";
			break;
		}
		break;

	case "fire":
		// ���湥��
		resistance = victim->query_temp("apply/resistance/fire");
		damage = (power + jingjia) * 100 / (100 + resistance);
		ITEM_D->receive_damage(me, victim, "qi", damage);
		switch (random(3))
		{
		case 0:
			msg = HIR + weapon->name() + HIR "�������һ�����棬��$n" HIR "�����������������ҽ�������"NOR"\n";
			break;
		case 1:
			msg = HIR "һ������" + weapon->name() + HIR "�ϱų���Ѹ�����׵Ļ���$n" HIR "�����˱��޿ɱܣ�"NOR"\n";
			break;
		default:
			msg = HIR "һ���������" + weapon->name() + HIR "�Ϸɽ����������ɢ������������$n" HIR "��"NOR"\n";
			break;
		}
		break;

	case "magic":
		// ħ������
		resistance = victim->query_temp("apply/resistance/magic");
		damage = (power + jingjia) * 100 / (100 + resistance);
		ITEM_D->receive_damage(me, victim, "qi", damage);
		switch (random(3))
		{
		case 0:
			msg = HIM + weapon->name() + HIM "����һ�������������������������$n" HIM "���񲻶��������㱡�"NOR"\n";
			break;
		case 1:
			msg = HIM "��࣡���һ����" + weapon->name() + HIM"����ܸȴ��$n" HIM "�ƺ�һ����ҡ�β�����"NOR"\n";
			break;
		default:
			msg = HIM + weapon->name() + HIM "������һ��������ͷ׵Ĺ�Ȧ��������$n" HIM "�����·��衣"NOR"\n";
			break;
		}
		break;
	case "all":
		switch (random(3))
		{
		case 0:
			msg = HIM "$N" HIM "��Ȼ��Ц������" + weapon->name() + HIM "�������⻪һ���������$n" HIM "���ڵ��У��޷��԰Ρ�"NOR"\n";
			break;
		case 1:
			msg = HIC "$N" HIC "���е�" + weapon->name() + HIC "������ֹ�â��ѣĿ���ˣ�һ�������ӳ�����ؾ���ʧɫ����$n" 
					HIC "Ŀ�ɿڴ���"NOR"\n";
			break;
		default:
			msg = HIW "$N" HIW "һ����̾��" + weapon->name() + HIW "����ݳ�����ʱ�����㾲��$n" HIW "ֻ���������˶������˵�����ȥ��"NOR"\n";
			break;
		}

		power = power/4;
		// ���繥��
		resistance = victim->query_temp("apply/resistance/lighting");
		damage = (power + jingjia) * 100 / (100 + resistance);
		ITEM_D->receive_damage(me, victim, "qi", damage);

		// �䶳�������˺���++����+
		resistance = victim->query_temp("apply/resistance/cold");
		damage = (power + jingjia) * 100 / (100 + resistance);
		ITEM_D->receive_damage(me, victim, "qi", damage);

		// ���湥�����˺���+����++
		resistance = victim->query_temp("apply/resistance/fire");
		damage = (power + jingjia) * 100 / (100 + resistance);
		ITEM_D->receive_damage(me, victim, "qi", damage);

		// ħ����������ȡ��+
		resistance = victim->query_temp("apply/resistance/magic");
		damage = (power + jingjia) * 100 / (100 + resistance);
		ITEM_D->receive_damage(me, victim, "qi", damage);

		if(!random(3))
		{
			msg += HIC "$N" HIC "������һ����Ц������" + weapon->name() + HIC "�϶�Ϊһ����Ҳ�Ƶ�����$n" HIC "��"NOR"\n";
			msg += HIR "$n" HIR "��֮�»�æ���ˣ�ȴ�����ܵÿ���һʱ�����������������˲��ᣡ\n";
			damage = power*3 + random(power);
			ITEM_D->receive_damage(me, victim, "qi", damage);
			ITEM_D->receive_wound(me, victim, "qi", damage);
		}
		break;
	default:
		msg += HIM "�������ˣ���֪ͨwiz����"NOR"\n";
		break;
	}
	if (random(3)) return msg;
}

// 9��������������
mixed weapon_hit_ob(object me, object victim, object weapon, int damage_bonus)
{
	int ap;
	int dp;
	int damage;

	if (random(2)) return;

	if (! living(victim)) return;

	// ����damage�������ǿ�������������ͨ������ͳһ����
	if (weapon->is_weapon())
		damage = me->query_temp("apply/damage");
	else
		damage = me->query_temp("apply/unarmed_damage");

	switch (random(6))
	{
	case 0:
		ITEM_D->receive_wound(me, victim, "jing", damage / 4 + random(damage / 4));
		return HIY "$N" HIY "�������е�" + weapon->name() + HIY
		       "���û���ҹ�����ǣ�����" HIM "��â" HIY "�ƿ�Ϯ��$n"
		       HIY "���⻪��Ŀ������Ŀѣ��"NOR"\n";
	case 1:
		ITEM_D->receive_wound(me, victim, "qi", damage / 2 + random(damage / 2));
		return HIR "$N" HIR "���һ�������е�" + weapon->name() +
		       HIR "ңָ$n" HIR "��һ��ɱ����ʱ��$n" HIR "����������"NOR"\n";

	case 2:
	case 3:
	case 4:
		break;

	default:
		if (me->query_temp("weapon_performing"))
			break;
		me->start_call_out(bind((: call_other, __FILE__, "continue_attack",me, victim, weapon, 2 :), me), 0);//�����2ԭ����5 + random(4)����ͳһ����Ϊ2
	}
}

// ���У�12��������
void continue_attack(object me, object victim, object weapon, int times)
{
	int i;
	string msg;
	int ap, dp;

	if (! me || ! victim || ! weapon || ! me->is_fighting(victim))
		return;

	if (! living(victim))
		return;

	msg  = HIC "\n$N" HIC "һ����Ц������" + weapon->name() +
	       HIC "�϶�Ϊһ����Ҳ�Ƶ�����$n" HIC "��"NOR"\n";
	ap = me->query_skill("force");
	dp = victim->query_skill("parry");
	if (ap / 2 + random(ap * 2) > dp)
		msg += HIR "$n" HIR "��֮�»�æ���ˣ�ȴ�����ܵÿ���һʱ��������������\n"
		       HIY "$N" HIY "ץס$n" HIY "¶�����������������е�" +
		       weapon->name() + HIY "������" + chinese_number(times) +
		       "��ȫ��ָ��$n" HIY "��Ҫ����"NOR"\n";
	else
	{
		msg += HIC "$n" HIC "ڤ��ֵ�����$N" HIC "���ɱһ�������б仯ȫȻ��ס��"NOR"\n";
		message_combatd(msg, me, victim);
		return;
	}

	message_combatd(msg, me, victim);

	if (! weapon->is_weapon())
		weapon = 0;

	me->set_temp("weapon_performing", 1);
	i = times;
	while (i--)
	{
		if (! me->is_fighting(victim)) break;
		if (! victim->is_busy() && random(2))
			victim->start_busy(1);
		COMBAT_D->do_attack(me, victim, weapon);
	}
	me->delete_temp("weapon_performing");
}

void receive_damage(object attack, object victim, string type, int damage)
{
	damage = COMBAT_D->calc_damage(attack, victim, damage);
	victim->receive_damage(type, damage);
}
void receive_wound(object attack, object victim, string type, int damage)
{
	damage = COMBAT_D->calc_wound(attack, victim, damage);
	victim->receive_wound(type, damage);
}
// �����;ö�
void reduce_consistence(object item)
{
	int st;
	int con;

	st = item->query("stable");
	if (st < 2) return;

	con = item->query("consistence");

	if (random(st) > (100 - con) / 12)
		return;
	
	if (item->add("consistence", -1) > 0)
		return;

	item->set("consistence", 0);
	if (environment(item))
		tell_object(environment(item), HIG "���" + item->name() + "�Ѿ��������ˡ�\n");
	item->unequip();
}

// ������Ʒȱʡ���;ö���Ϣ
void equip_setup(object item)
{
	int stable;
	mapping prop,dbase;
	int i,k;
	string *attr_list = ({
		"damage",
		"armor",
                "attack",
                "parry",
                "dodge",
                "strength",
                "intelligence",
                "constitution",
                "dexerity",
                "karma",
                "personality",
                "speed",
                "maxqi",
                "maxnei",
	});

	for(i=0;i<sizeof(attr_list);i++)
	{
		if(k=item->query("armor_prop/"+attr_list[i]))
			item->set("armor_prop/"+attr_list[i], k);
		if(k=item->query("weapon_prop/"+attr_list[i]))
			item->set("weapon_prop/"+attr_list[i], k);
	}

	dbase = item->query_entire_dbase();
	if (undefinedp(dbase["consistence"]))
		dbase["consistence"] = 100;

	if (undefinedp(item->query("stable")))
	{
		switch (item->query("material"))
		{
		case "cloth":
			// ��Զ������
			stable = 0;
			break;

		case "paper":
			stable = 3;
			item->set("no_repair", "�ⶫ���ҿ�û������\n");
			break;

		case "bone":
			stable = 8;
			item->set("no_repear", "����������ɱ�����Ѱ���ġ�\n");
			break;

		case "bamboo":
		case "wood":
			stable = 10;
			item->set("no_repair", "�ⶫ����զ����\n");
			break;

		case "stone":
			stable = 20;
			item->set("no_repair", "������˾ͻ��ˣ����޲��ˡ�\n");
			break;

		case "copper":
			stable = 40;
			break;

		case "silver":
			stable = 40;
			break;

		case "iron":
			stable = 45;
			break;

		case "gold":
			stable = 50;
			break;

		case "steel":
			stable = 75;
			break;

		default:
			stable = 100;
			break;
		}

		if (! item->is_item_make())
			stable /= 2;

		item->set("stable", stable);
	}
}
