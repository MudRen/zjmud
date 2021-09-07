// daub.c

#include <ansi.h>

inherit F_CLEAN_UP;

// the flag that wether I know there is some poison on the object
#define I_KNOW		  1
#define I_DONT_KNOW	     0

void check_poison(object me, object dest, int iknow);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string item, target;
	object obj, dest;

	if (!arg)
		return notify_fail("��Ҫ���Ķ�ͿĨ��ҩ��\n");

	if (me->is_busy())
		return notify_fail("��æ�����������������ô���˰ɣ�\n");

	if (me->is_fighting())
		return notify_fail("���������ڴ�ܣ�ûʱ������Щ���顣\n");

	if (sscanf(arg, "with %s", item) == 1)
		target = "hand";
	else
	if (sscanf(arg, "%s with %s", target, item) == 2)
		;
	else
	if (sscanf(arg, "%s on %s", item, target) == 2)
		;
	else
		return notify_fail("��Ҫ���Ķ�ͿĨ��ҩ��\n");

	if (! present("hand", me) && target == "hand" ||
	    target == "me")
	{
		// daub on me
		dest = me;
	} else
	{
		dest = present(target, me);
		if (! dest) dest = present(target, environment(me));
		if (! dest)
			return notify_fail("����û������������\n");

		if (dest->is_character())
		{
			if (dest != me && ! dest->is_corpse())
			{
				return notify_fail("����" + dest->name() +
						   "����Ϳʲô���ұⰡ��\n");
			}
			// daub on me
		} else
		if (! mapp(dest->query("armor_prop")) &&
		    ! mapp(dest->query("weapon_prop")))
		{
			return notify_fail("�ǼȲ���������Ҳ���Ƿ��ߣ�"
					   "����ôͿĨ��ҩ�أ�\n");
		}
	}

	if (!objectp(obj = present(item, me)))
		return notify_fail("������û������������\n");

	if (!stringp(obj->query("poison_type")))
		return notify_fail(obj->name() + "���Ƕ�ҩ����\n");

	if (! obj->query("can_daub"))
		return notify_fail("���ֶ�ҩ��������ͿĨ��\n");

	dest->set_temp("daub/who_id", me->query("id"));
	dest->set_temp("daub/who_name", me->query("name"));
	dest->set_temp("daub/poison_name", obj->name());
	dest->set_temp("daub/poison_type", obj->query("poison_type"));
	dest->set_temp("daub/poison",
		POISON->mixed_poison(dest->query_temp("daub/poison"), obj->query("poison")));
	if (dest == me)
	{
		message("vision", sprintf("%s�ó�һЩ�������Լ�����Ϳ��"
					  "Ĩȥ�ģ���֪���ڸ�ʲô��\n",
					  me->name()), environment(me), ({ me }));
		tell_object(me, HIG "���" + obj->name() + HIG "ͿĨ���Լ����ϡ�"NOR"\n");
		check_poison(me, dest, I_KNOW);
		destruct(obj);
		return 1;
	}

	message("vision", sprintf("%s�ó�һЩ����ͿĨ��%s���档\n",
				  me->name(), dest->name()),
			  environment(me), ({ me }));
	tell_object(me, HIG "���" + obj->name() + HIG "ͿĨ��" + dest->name() + HIG "�ϡ�"NOR"\n");
	if (dest->query("equipped") == "worn" &&
	    dest->query("armor_type") != "hands" &&
	    environment(dest) == me)
	{
		// daub on armor that I am wearing
		check_poison(me, dest, I_KNOW);
	}

	if (obj->query_amount() > 1)
		obj->add_amount(-1);
	else
		destruct(obj);
	return 1;
}

// check wether I can sufface the poison
void check_poison(object me, object dest, int iknow)
{
	string name;
	string type;
	mapping p;
	int lvl;

	if (! dest) dest = me;
	name = dest->query_temp("daub/poison_name");
	type = dest->query_temp("daub/poison_type");
	p    = dest->query_temp("daub/poison");
	if (! name || ! p || ! type) return;

	if (p["id"] == me->query("id"))
		// The poison is made by me
		return;

	lvl = me->query_skill("force") + me->query("poison", 1) / 2;
	if (lvl < 100 || lvl < (int)p["level"])
	{
		message("vision", HIC "��Ȼ" + me->name() + HIC "üͷ"
				  "����������ʹ�࣬�����������鷳�ˡ�"NOR"\n",
				  environment(me), ({ me }));
		tell_object(me, HIC "��Ȼ������е㲻�Ծ������ã��������ж��ˡ�"NOR"\n");
		me->affect_by(type, p);
		dest->delete_temp("daub");
		return;
	}

	message("vision", HIC + me->name() + HIC "üͷ"
			  "΢΢һ�壬�漴��չ������"NOR"\n",
			  environment(me), ({ me }));

	if (p["level"] > 120)
	{
		if (iknow)
			tell_object(me, HIC "�㷢����" + name + HIC "������"
					"�����ң��Һ��ڹ�����ֵ���ס��"NOR"\n");
		else
			tell_object(me, HIC "�㷢����" + dest->name() + HIC "�ϵ�" +
					name + HIC "������"
					"�����ң��������ڹ�������������¡�"NOR"\n");
	} else
	if (! iknow && dest->query_temp("who_id") != me->query("id"))
	{
		tell_object(me, HIC "�㷢����" + name + HIC "���������"NOR"\n");
	}
}

int help(object me)
{
write(@HELP
ָ���ʽ : daub <��Ʒ����> on <����> | <����> | hand
	   daub <����> | <����> | [hand] with <��Ʒ����>

���ָ��������㽫ĳ����ƷͿĨ�������ϣ����߻������ϣ���Ȼ��ͿĨ��
���߻������ϵĵĶ���ò�Ҫʹ�Լ��ж���
HELP
    );
    return 1;
}
