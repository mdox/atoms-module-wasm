#define WASM_EXPORT __attribute__((visibility("default")))

#define x(v) v[0]
#define y(v) v[1]

WASM_EXPORT void rule(
    int a_atoms_count,
    float *a_position_array,
    float *a_velocity_array,

    int b_atoms_count,
    float *b_position_array,

    float range,
    float gravity)
{
  float rangeSq = range * range;

  float *a_position;
  float *a_position_end = a_position_array + a_atoms_count * 2;
  float *a_velocity = a_velocity_array;

  float *b_position;
  float *b_position_end = b_position_array + b_atoms_count * 2;

  for (a_position = a_position_array; a_position != a_position_end; a_position += 2, a_velocity += 2)
  {
    float fx = 0.0f;
    float fy = 0.0f;
    for (b_position = b_position_array; b_position != b_position_end; b_position += 2)
    {
      float dx = x(a_position) - x(b_position);
      float dy = y(a_position) - y(b_position);
      float dSq = dx * dx + dy * dy;
      if (dSq > 0 && dSq < rangeSq)
      {
        float F = gravity / __builtin_sqrtf(dSq);
        fx += F * dx;
        fy += F * dy;
      }
    }
    x(a_velocity) = (x(a_velocity) + fx) * 0.5f;
    y(a_velocity) = (y(a_velocity) + fy) * 0.5f;
    x(a_position) = (x(a_velocity) + x(a_position));
    y(a_position) = (y(a_velocity) + y(a_position));
    if (x(a_position) < -1 || x(a_position) > 1)
      x(a_velocity) = -0.01f * x(a_position);
    if (y(a_position) < -1 || y(a_position) > 1)
      y(a_velocity) = -0.01f * y(a_position);
  }
}
