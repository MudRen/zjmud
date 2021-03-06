// emote.c (Mon  09-04-95)

#include <ansi.h>

inherit F_CLEAN_UP;
 
int main(object me, string str)
{
	string *emotes,prefix,estr;
	object env;
	mixed info;
	int i;

	if (me->ban_say())
		return 0;

	env = environment(me);
	if (info = env->query("no_say"))
	{
		if (stringp(info))
		{
			write(info);
			return 1;
		}

		write("这个地方不能乱做动作。\n");
		return 1;
	}

	if (! str)
	{
		emotes = EMOTE_D->query_all_emote();
		estr = ZJOBLONG+"当前频道【"+me->query_temp("pindao/name")+"】，请选择表情动作：\n"ZJOBACTS2+ZJMENUF(3,3,8,30);
//		for(i=0;i<sizeof(emotes);i++)
		for(i=0;i<10;i++)
		{
			estr += emotes[i]+":"+me->query_temp("pindao/id")+"* "+emotes[i]+ZJSEP;
		}
		write(estr+"\n");
		return 1;
	}

	prefix = me->query("env/no_prefix") ? "" : "～";
	write(CYN "你" + str + ""NOR"\n");
	tell_room(env, CYN + prefix + (string)me->name() +  str + ""NOR"\n", me);
	return 1;
}
 
int help(object me)
{
	write(@HELP
指令格式: emote <动作词>

这个指令可以让你表达一个系统没有预设的动作词, 系统会将你所输入
的文字加上你的姓名後显示给所有在同一个地方的生物看。为了避免造
成困扰, 玩家所输入的词句前面会加上 ~ 以供区别。

范例: emote 坐了下来。
你会看见: 你坐了下来。
其他人会看到: ~包子坐了下来。

其中, 包子就是你的名字.

相关指令: semote
HELP );
	return 1;
}
