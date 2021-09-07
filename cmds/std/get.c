// Filename : /cmds/verb/get.c

#include <ansi.h>
#include <command.h>
#include <config.h>

inherit F_CLEAN_UP;

int do_get(object me, object ob, int raw);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string from, item, where, tmp;
	object obj, *inv, env, obj2;
	mixed info;
	string msg;
	int i, amount;

	if (! arg) return notify_fail("��Ҫ����ʲ�ᶫ����\n");

	// Check if a container is specified.
	if (sscanf(arg, "%s from %s", arg, from) == 2)
	{
		if(sscanf(from,"%s of %s",tmp,where) == 2)
		{
			from = tmp;
		}
		else
		{
			where = "all";
		}
		if(where != "me" && where != "here")
		{
		env = present(from, me);
		if (! env) env = present(from, environment(me));		
		}
		else if(where == "me")
		{
			env = present(from, me);
		}
		else
		{
			env = present(from, environment(me));
		}
		if (! env) return notify_fail("���Ҳ��� " + from + " ����������\n");
		if (me == env) return notify_fail("ë������Ҫ���Լ�����\n");
		if (env->query("no_get_from") || living(env) || playerp(env))
		{
			if (! wizardp(me))
				return notify_fail("�㲻������\n");

			if (wiz_level(me) <= wiz_level(env) &&
			    ! MASTER_OB->valid_write(base_name(env), me, "get"))
				return notify_fail("�����ʦ�ȼ�����ȶԷ��߲�������\n");

			if (wiz_level(me) < 3)
				return notify_fail("�����ʦ�ȼ���������\n");
		}
	} else env = environment(me);

	// Check if a certain amount is specified.
	if (sscanf(arg, "%d %s", amount, item) == 2)
	{
		if (! objectp(obj = present(item, env)))
			return notify_fail("����û������������\n");

		if (! obj->query_amount())
			return notify_fail( obj->name() + "���ܱ��ֿ����ߡ�\n");

		if (amount < 1)
			return notify_fail("�����ĸ���������һ����\n");

		if (amount > obj->query_amount())
			return notify_fail("����û��������" + obj->name() + "��\n");

		else if (amount == (int)obj->query_amount())
		{
			// get object when fighting costs time
			if (me->is_fighting() && ! me->is_busy()) me->start_busy(1);
			return do_get(me, obj, 0);
		} else
		{
			obj->set_amount((int)obj->query_amount() - amount);
			obj2 = new(base_name(obj));
			obj2->set_amount(amount);
			// Counting precise amount costs more time.
			if (me->is_fighting() && ! me->is_busy()) me->start_busy(3);
			if (! do_get(me, obj2, 0))
			{
				obj2->move(env);
				return 0;
			}
			return 1;
		}
	}

	// Check if we are makeing a quick get.
	if (arg == "all")
	{
		object my_env;

		if (wiz_level(me) < 3)
			return notify_fail("ÿ��ֻ����һ��������\n");

		if (me->is_fighting())
			return notify_fail("�㻹��ս���У�ֻ��һ����һ����\n");

		if (! env->query_max_encumbrance())
			return notify_fail("�ǲ���������\n");

		my_env = environment(me);
		inv = all_inventory(env);
		for (i = 0, amount = 0; i < sizeof(inv); i++)
		{
			if (! living(me)) break;
			if (environment(me) != my_env) break;
			if (inv[i]->is_character() || inv[i]->query("no_get"))
				continue;
			amount += do_get(me, inv[i], 1);
		}
		if (! amount)
		{
			write("��ʲô��û�м�������\n");
			return 1;
		}

		if (env->is_character())
			msg = me->name() + "��" + env->name() + "�����ѳ���һ�Ѷ�����\n";
		else
		if (env == my_env)
			msg = me->name() + "�ѵ��ϵĶ���������������\n";
		else
			msg = me->name() + "��" + env->name() + "����Ķ��������˳�����\n";
		message("vision", msg, environment(me), ({ me }));
		write("����ˡ�\n");
		return 1;
	}

	if (! objectp(obj = present(arg, env)) || living(obj))
		return notify_fail("�㸽��û������������\n");

	if (info = obj->query("no_get")&&!wizardp(me))
		return notify_fail(stringp(info) ? info : "��������ò�������\n");

	// get object when fighting costs time
	if (me->is_fighting() && ! me->is_busy()) me->start_busy(1);

	return do_get(me, obj, 0);
}
	
int do_get(object me, object obj, int raw)
{
	object old_env, *guard;
	string msg;
	int num,equipped;
	object *obs;

	if (! obj) return 0;
	old_env = environment(obj);

	if (obj->is_character() && living(obj)) return 0;
	if (obj->query("no_get")&& wiz_level(me) < 3 ) return 0;

	if (guard = obj->query_temp("guarded"))
	{
		guard = filter_array(guard, (: objectp($1) && present($1, environment($2)) &&
					       living($1) && ($1 != $2) :), me);
		if (sizeof(guard))
			return notify_fail( guard[0]->name() 
				+ "������" + obj->name() + "һ�ԣ���ֹ�κ������ߡ�\n");
	}

	if (obj->query("equipped")) equipped = 1;
	obs = filter_array(all_inventory(me), (: ! $1->query("equipped") :));
	if (sizeof(obs) >= MAX_ITEM_CARRIED &&
	    ! obj->can_combine_to(me)&&!wizardp(me))
		return notify_fail("�����ϵĶ���ʵ����̫���ˣ�û�����ö����ˡ�\n");
	
	//if(playerp(obj))
	if (obj->is_character() && obj->query("race") == "����")
		return notify_fail("����Ϸ��֧�ְѻ�������������\n");

	if (obj->query_amount()) num = obj->query_amount();
	if (obj->move(me))
	{
		if (obj->is_character() && obj->query_weight() > 20000)
		{
			object cloth;
			int iknow;
			message_vision("$N��$n�����������ڱ��ϡ�\n", me, obj);
			cloth = obj->query_temp("armor/cloth");
			iknow = me->query("name") + "��ʬ��" == obj->name();
			if (cloth)
			{
				// is the cloth daub with poison ?
				DAUB_CMD->check_poison(me, cloth, iknow);
			} else
			{
				// is the corpse daub with poison ?
				DAUB_CMD->check_poison(me, obj, iknow);
			}
		} else
		{
			msg = sprintf("$N%s%s%s%s��\n",
				(! old_env || old_env == environment(me)) ? "����" :
				old_env->is_character() ?  "��" + old_env->name() + "����" + (equipped ? "����" : "�ѳ�") :
				old_env->is_tree() ? "��" + old_env->name() +"��ժ��" : "��" + old_env->name() + "���ó�",
				obj->query_amount()?CHINESE_D->chinese_number(num):"һ",
				obj->query_amount()?obj->query("base_unit"):obj->query("unit"),
				obj->query("name"));
			if (! raw)
				message_vision(msg, me);
			else
				write(replace_string(msg, "$N", "��"));
		}
		return 1;
	}
	else return 0;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : get <��Ʒ����> | all [from <������>]
 
���ָ��������������ϻ������ڵ�ĳ����Ʒ.
 
�������ڿ��Ա���Ȩʹ�õ���Ϣ������noneuser��user��all��
HELP );
	return 1;
}
